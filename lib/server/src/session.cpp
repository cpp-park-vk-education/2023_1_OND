#include "session.hpp"
#include <boost/bind/bind.hpp>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "package.hpp"

Session::Session(tcp::socket socket, std::shared_ptr <Handler> handler):
    socket_(std::move(socket)), handler_(handler) {}

void Session::start() {
    std::cout << "====================+START+==========================" << std::endl;
    // main2();
    // // handler_->serve(shared_from_this(), shared_from_this());
    // // return;
    // std::cout << "START" << std::endl;
    // // async_read();

    // boost::asio::read(socket_, boost::asio::buffer(data_, 8));
    // std::stringstream strHex;
    // data_[8] = 0;
    // strHex << std::string(data_);
    // std::cout << strHex.str() << std::endl;
    // int k;
    // strHex >> std::hex >> k;
    // std::cout << k << " :размер данных" << std::endl;
    // char ncn[1024];
    // while (k >= 1024) {
    //     boost::asio::read(socket_, boost::asio::buffer(data_, 1024));
    //     read_buf_.write(data_, 1024);
    //     // socket_.async_read_some(boost::asio::buffer(data_, 1024),
    //     //     boost::bind(&Session::on_read, this,
    //     //     boost::asio::placeholders::error,
    //     //     boost::asio::placeholders::bytes_transferred));
    //     k -= 1024;
    // }
    // if (k > 0) {
    //     boost::asio::read(socket_, boost::asio::buffer(data_, k));
    //     read_buf_.write(data_, k);
    //     // socket_.async_read_some(boost::asio::buffer(data_, k),
    //     //     boost::bind(&Session::on_read, this,
    //     //     boost::asio::placeholders::error,
    //     //     boost::asio::placeholders::bytes_transferred));
    // }
    // handler_->serve(shared_from_this(), shared_from_this());

    std::cout << "============START=NEW=LEVEL================" << std::endl;
    m_async_read();

}

std::size_t Session::read(Package & pkg) {
    pkg = pkgs_on_read_.front();
    pkgs_on_read_.pop();
    // read_buf_ >> str;
    // str = read_buf_.str();
    // // std::getline(read_buf_, str);
    // return str.size();



    // while (pkgs_on_read_.empty()) {
    //     std::cout << -2 << std::endl;
    // }
    // str = pkgs_on_read_.front().text;
    // pkgs_on_read_.pop();
    return 0;
}

std::size_t Session::write(const Package & pkg) {
        // int length = str.size();
        // std::stringstream ss;
        // ss << std::setw(8) << std::hex << length;
        // std::string head = ss.str();
        // std::cout << "WRITE" << std::endl;
        // std::cout << head << std::endl;
        // std::cout << "WEND" << std::endl;
        // boost::asio::write(socket_, boost::asio::buffer(head.c_str(), 8));
        // boost::asio::write(socket_, boost::asio::buffer(str.c_str(), length));

        pkgs_on_write_.push(pkg);
        m_async_write();

        // if (queue_on_write_.empty()) {
        //     queue_on_write_.push(str);
        //     async_write();
        // } else {
        //     queue_on_write_.push(str);
        // }
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
    read_buf_.write(data_, bytes_transferred);
    // std::cout << error.to_string() << "+++++" << bytes_transferred << std::endl;
    // std::cout << "read 8b" << strlen(data_) << std::endl;
    // std::cout << (int) data_[1011] << std::endl;
    // if (!error) {
    //     read_buf_ << std::istream(&streambuf).rdbuf();
    //     handler_->serve(shared_from_this(), shared_from_this());
    //     async_read();
    // } else {
    //     socket_.close(error);
    // }
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
