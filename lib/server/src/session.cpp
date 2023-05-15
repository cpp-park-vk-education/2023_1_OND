#include "session.hpp"

Session::Session(tcp::socket socket, std::shared_ptr <Handler> handler):
    socket_(std::move(socket)), handler_(handler) {}

void Session::start() {
    async_read();
}

std::size_t Session::read(std::string & str) {
    str.clear();
    read_buf_ >> str;
    return str.size();
}

std::size_t Session::write(const std::string & str) {
        if (queue_on_write_.empty()) {
            queue_on_write_.push(str);
            async_write();
        } else {
            queue_on_write_.push(str);
        }
        return 0;
}

void Session::async_read() {
    boost::asio::async_read_until(
        socket_,
        streambuf,
        "\nend\n",
        std::bind(&Session::on_read, shared_from_this(),
            std::placeholders::_1,
            std::placeholders::_2)
    );
}

void Session::on_read(boost::system::error_code error, std::size_t bytes_transferred) {
    if (!error) {
        read_buf_ << std::istream(&streambuf).rdbuf();
        handler_->serve(shared_from_this(), shared_from_this());
        async_read();
    } else {
        socket_.close(error);
    }
}

void Session::async_write() {
    boost::asio::async_write(
        socket_,
        boost::asio::buffer(queue_on_write_.front()),
        std::bind(&Session::on_write, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
}

void Session::on_write(boost::system::error_code error, std::size_t bytes_transferred) {
    if (!error) {
        queue_on_write_.pop();
        if (!queue_on_write_.empty()) {
            async_write();
        }
    } else {
        socket_.close(error);
    }
}
