#include "server.hpp"

ServerTCP::ServerTCP(boost::asio::io_context& io_context, short port): acceptor_(io_context, tcp::endpoint(tcp::v4(), port)), handler_(nullptr) {
    doAccept();
}

void ServerTCP::doAccept() {
    acceptor_.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket) {
          if (!ec) {
            std::make_shared<Session>(std::move(socket), handler_)->start();
          }

          doAccept();
        });
}
void ServerTCP::setHandler(std::shared_ptr <Handler> handler) {
    handler_ = handler;
}
