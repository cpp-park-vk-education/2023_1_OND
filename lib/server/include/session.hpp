#pragma once
#include <memory>
#include <boost/asio.hpp>
#include <iostream>
#include <queue>

#include "interfaces.hpp"
#include "server.hpp"

using tcp = boost::asio::ip::tcp;

const int MAX_LENGTH = 1024;

class Session: public Writer, public Reader, public std::enable_shared_from_this<Session> {
private:
    tcp::socket socket_;
    char data_[MAX_LENGTH];
    std::shared_ptr <Handler> handler_;
    boost::asio::streambuf streambuf;
    std::stringstream read_buf_;
    std::queue<std::string> queue_on_write_;

    void start();
    void async_read();
    void on_read(boost::system::error_code error, std::size_t bytes_transferred);
    void async_write();
    void on_write(boost::system::error_code error, std::size_t bytes_transferred);

public:

    Session(tcp::socket socket, HandlerSPtr handler);
    std::size_t read(std::string & str) override;
    std::size_t write(const std::string & str) override;

    friend class ServerTCP;
};
