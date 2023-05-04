#pragma once
#include <boost/asio.hpp>
#include <memory>

#include "interfaces.hpp"
#include "session.hpp"


class ServerTCP {
private:
    tcp::acceptor acceptor_;
    std::shared_ptr <Handler> handler_;

    void doAccept();

public:
    ServerTCP(boost::asio::io_context& io_context, short port);
    ServerTCP(const ServerTCP & server) = delete;
    ServerTCP& operator=(const ServerTCP & server) = delete;
    ~ServerTCP() = default;
    void setHandler(HandlerSPtr handler);
};
