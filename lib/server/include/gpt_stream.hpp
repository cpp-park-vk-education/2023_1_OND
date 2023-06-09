#pragma once
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
#include "interfaces.hpp"
#include "api.hpp"
#include "ssl.hpp"

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;
using json = nlohmann::json;


class StreamGPT : public std::enable_shared_from_this<StreamGPT> {
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
    explicit StreamGPT(net::io_context& ioc, ssl::context & ctx,
            std::shared_ptr<ITTS> tts, WriterSPtr w, const std::string & voice);

    void run(char const* host, char const* port, char const* target, 
        int version, const std::string & question, 
        const std::string & token_gpt);

    void on_write(
        beast::error_code ec,
        std::size_t bytes_transferred);

    void read_event(boost::system::error_code ec);

    void on_read(beast::error_code ec, std::size_t bytes_transferred);
};

void ask_gpt(const std::string & question, std::shared_ptr<ITTS> tts,
        WriterSPtr w, const std::string & voice,
        const std::string & token_gpt);
