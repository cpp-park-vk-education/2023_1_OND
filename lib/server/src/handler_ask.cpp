#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/strand.hpp>
#include <cstdlib>
#include <memory>
#include <string>
#include <boost/beast/http/buffer_body.hpp>
#include <boost/beast/http/parser.hpp>
#include <boost/asio/ssl.hpp>
#include <nlohmann/json.hpp>
#include "ssl.hpp"
#include "interfaces.hpp"
#include "package.hpp"
#include "handler.hpp"
namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;
using json = nlohmann::json;


void fail(beast::error_code ec, char const* what) {
    std::cerr << what << ": " << ec.message() << "\n";
}

class session : public std::enable_shared_from_this<session> {
private:   
    tcp::resolver resolver_;
    ssl::stream<tcp::socket> stream_;
    beast::flat_buffer buffer_;
    http::request<http::string_body> req_;
    http::response<http::string_body> res_;
    http::parser <false, http::string_body> p_;
    boost::asio::ip::basic_resolver_results<boost::asio::ip::tcp> results_;
    std::ostringstream text_;
    std::shared_ptr<ITTS> tts_;
    WriterSPtr w_;
    std::string voice_;


public:
    explicit session(net::io_context& ioc, ssl::context & ctx,
            std::shared_ptr<ITTS> tts, WriterSPtr w, const std::string & voice): resolver_(ioc),
            stream_(ioc, ctx), tts_(tts), w_(w), voice_(voice) {}

    void run(
        char const* host,
        char const* port,
        char const* target,
        int version,
        const std::string & question,
        const std::string & token_gpt)
    {
        if (!SSL_set_tlsext_host_name(stream_.native_handle(), host)) {
            boost::system::error_code ec{static_cast<int>(::ERR_get_error()),
                boost::asio::error::get_ssl_category()};
            throw boost::system::system_error{ec};
        }
        results_ = resolver_.resolve(host, port);
        boost::asio::connect(stream_.next_layer(), results_.begin(), results_.end());
        stream_.handshake(ssl::stream_base::client);

        req_.version(version);
        req_.method(http::verb::post);
        req_.target(target);
        req_.set(http::field::host, host);
        req_.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
        req_.set(http::field::authorization, "Bearer " + token_gpt);
        req_.set(http::field::content_type, "application/json");
        std::string bodyd = "{\"model\": \"gpt-3.5-turbo\",\
                \"messages\": [{\"role\": \"user\", \"content\": \"" + question + "\"}],\
                \"stream\": true}";
        req_.set(http::field::content_length, std::to_string(bodyd.size()));
        req_.body() = bodyd;
        std::cout << "fdssfdfd" << std::endl;
        http::async_write(stream_, req_,
            beast::bind_front_handler(
                &session::on_write,
                shared_from_this()));
    }

    void on_write(
        beast::error_code ec,
        std::size_t bytes_transferred) {
        boost::ignore_unused(bytes_transferred);
        if(ec)
            return fail(ec, "write");
        std::cout << "HI" << std::endl;
        read_event(ec);
    }

    void read_event(boost::system::error_code ec) {
        http::async_read_some(stream_, buffer_, p_,
            beast::bind_front_handler(
            &session::on_read,
            shared_from_this()));
    }

    void read_event1(boost::system::error_code ec) {
        std::cout << 1 << std::endl;
    }

    void on_read(beast::error_code ec, std::size_t bytes_transferred) {
        boost::ignore_unused(bytes_transferred);
        if (ec.value() == 9) {
            return;
        }
        std::string event = p_.get().body();
        bool end = false;
        if (event.size() > 2) {
            event.pop_back();
            event.pop_back();
            if (event.size() > 7 && event.substr(event.size() - 6, 6) == "[DONE]") {
                end = true;
            }
            std::string delta;
            try {
                json resJSON = json::parse(event.substr(6));
                delta = resJSON["choices"][0]["delta"]["content"];
            } catch (std::exception & e) {
                delta = ".Exception.";
            }
            text_ << delta;
            if (delta == "." || delta == "\n" || 
                    delta == "," && text_.str().size() > 20 || end) {
                std::cout << "Уже можно отправлять сдедующее: " 
                    << text_.str() << std::endl;
                Package p;
                std::string voice;
                tts_->speak(text_.str(), voice_, voice);
                p.voice = voice;
                p.finish = end;
                w_->write(p);
                text_ = std::ostringstream();
            }
        }
        p_.get().body().clear();
        if (!end) {
            read_event(ec);
        }
        if(ec && ec != beast::errc::not_connected)
            return fail(ec, "shutdown");
    }
};


void ask_gpt(const std::string & question, std::shared_ptr<ITTS> tts,
        WriterSPtr w, const std::string & voice,
        const std::string & token_gpt) {
    std::cout << "adk_gpt: You ask the gpt" << std::endl;
    auto const host = "api.openai.com";
    auto const port = "443";
    auto const target = "/v1/chat/completions";
    int version = 11;

    net::io_context ioc;
    ssl::context ctx{ssl::context::sslv23_client};

    load_root_certificates(ctx);

    ctx.set_verify_mode(ssl::verify_peer);

    std::make_shared<session>(ioc, ctx, tts, w, voice)->run(host, port, 
        target, version, question, token_gpt);

    ioc.run();
}


Ask::Ask(DatabaseSPtr db, std::shared_ptr<APIChatGPT> gpt,
         std::shared_ptr<IASR> asr,
         const std::vector<std::shared_ptr<ITTS>> & tts,
         const std::string & token_gpt):
            db_(db), gpt_(gpt), asr_(asr), tts_(tts),
            token_gpt_(token_gpt) {}

void Ask::serve(WriterSPtr w, ReaderSPtr r) {
    std::cout << "----ASK START-----" << std::endl;

    Package pkg;
    r->read(pkg);
    std::cout << "Пакет получен" << std::endl;

    std::chrono::_V2::steady_clock::time_point begin;
    std::chrono::_V2::steady_clock::time_point end;
    std::chrono::milliseconds elapsed_ms;


    std::string question_text;
    begin = std::chrono::steady_clock::now();
    asr_->trans(pkg.voice, question_text);
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time: " << elapsed_ms.count() << " ms\n";
    std::cout << "Получен следующий вопрос: " << question_text << std::endl;

    int tts_num = std::stoi(pkg.param["tts"]);
    std::cout << "number tts " << tts_num << std::endl;
    std::string answer;
    if (pkg.param.find("stream") != pkg.param.end()) {
        // В текущей версии приложения
        // такой формат не поддерживается со стороны клиента,
        // и предполагается, что пакет с таким параметром придти не может,
        // поэтому реализация получения ответа от ChatGPT с использованием SSE
        // на стороне сервера написана в качестве эксперимента и в релизной версии
        // продукта не используется, поэтому внимание на качество кода не уделялось.
        ask_gpt(question_text, tts_[tts_num], w, pkg.param["voice"], token_gpt_);
    }

    std::cout << "Спросим у ChatGPT" << std::endl;
    begin = std::chrono::steady_clock::now();
    gpt_->ask("", question_text, answer);
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time: " << elapsed_ms.count() << " ms\n";
    std::cout << "Ответ от ChatGPT: " << answer << std::endl;


    std::string data;
    begin = std::chrono::steady_clock::now();
    tts_[tts_num]->speak(answer, pkg.param["voice"], data);
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time: " << elapsed_ms.count() << " ms\n";
    std::cout << "получена озвучка: " << data.size() << std::endl;


    Package npkg;
    npkg.finish = true;
    npkg.text = answer;
    npkg.voice = data;
    npkg.param["tts"] = pkg.param["tts"];
    w->write(npkg);
}
