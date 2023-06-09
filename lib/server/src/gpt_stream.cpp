#include "gpt_stream.hpp"

void fail(beast::error_code ec, char const* what) {
    std::cerr << what << ": " << ec.message() << "\n";
}

StreamGPT::StreamGPT(net::io_context& ioc, ssl::context & ctx,
            std::shared_ptr<ITTS> tts, WriterSPtr w, const std::string & voice): resolver_(ioc),
            stream_(ioc, ctx), tts_(tts), w_(w), voice_(voice) {}

void StreamGPT::run(
        char const* host,
        char const* port,
        char const* target,
        int version,
        const std::string & question,
        const std::string & token_gpt) {
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
            &StreamGPT::on_write,
            shared_from_this()));
}

void StreamGPT::on_write(
    beast::error_code ec,
    std::size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);
    if(ec)
        return fail(ec, "write");
    std::cout << "HI" << std::endl;
    read_event(ec);
}

void StreamGPT::read_event(boost::system::error_code ec) {
    http::async_read_some(stream_, buffer_, p_,
        beast::bind_front_handler(
        &StreamGPT::on_read,
        shared_from_this()));
}

void StreamGPT::on_read(beast::error_code ec, std::size_t bytes_transferred) {
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

void ask_gpt(const std::string & question, std::shared_ptr<ITTS> tts,
        WriterSPtr w, const std::string & voice,
        const std::string & token_gpt) {
    std::cout << "ask_gpt: You ask the gpt" << std::endl;
    auto const host = "api.openai.com";
    auto const port = "443";
    auto const target = "/v1/chat/completions";
    int version = 11;

    net::io_context ioc;
    ssl::context ctx{ssl::context::sslv23_client};

    load_root_certificates(ctx);

    ctx.set_verify_mode(ssl::verify_peer);

    std::make_shared<StreamGPT>(ioc, ctx, tts, w, voice)->run(host, port, 
        target, version, question, token_gpt);

    ioc.run();
}
