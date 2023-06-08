#pragma once
#include <memory>
#include <boost/asio.hpp>
#include <iostream>
#include <queue>
#include <boost/bind/bind.hpp>

#include "interfaces.hpp"
#include "server.hpp"
#include "package.hpp"

using tcp = boost::asio::ip::tcp;

class Session: public Writer, public Reader, public std::enable_shared_from_this<Session> {
private:
    tcp::socket socket_;
    std::shared_ptr <Handler> handler_;
    std::queue <Package> pkgs_on_read_;
    std::queue <Package> pkgs_on_write_;
    enum { header_length = 8 };
    std::string outbound_header_;
    std::string outbound_data_;
    char inbound_header_[header_length];
    std::vector<char> inbound_data_;

    void start();
    void async_read();
    void async_write();
    void handle_read_header(const boost::system::error_code& e);
    void handle_read_data(const boost::system::error_code& e);

public:
    Session(tcp::socket socket, HandlerSPtr handler);
    std::size_t read(Package & pkg) override;
    std::size_t write(const Package & pkg) override;

    friend class ServerTCP;
};
