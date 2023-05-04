#pragma once
#include <memory>
#include <boost/asio.hpp>
#include <iostream>

#include "interfaces.hpp"
#include "server.hpp"

using tcp = boost::asio::ip::tcp;

const int MAX_LENGTH = 1024;

class Session: public Writer, public Reader, public std::enable_shared_from_this<Session> {
private:
    tcp::socket socket_;
    char data_[MAX_LENGTH];
    std::shared_ptr <Handler> handler_;

    void start();

public:

    Session(tcp::socket socket, HandlerSPtr handler);
    std::size_t read(std::string & str) override;
    std::size_t write(const std::string & str) override;

    friend class ServerTCP;
};
