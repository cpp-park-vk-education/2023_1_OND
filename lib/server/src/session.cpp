#include "session.hpp"

Session::Session(tcp::socket socket, std::shared_ptr <Handler> handler): socket_(std::move(socket)), handler_(handler) {}

void Session::start() {
    handler_->serve(shared_from_this(), shared_from_this());
}

std::size_t Session::read(std::string & str) {}

std::size_t Session::write(const std::string & str) {}
