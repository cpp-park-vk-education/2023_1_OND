#pragma once
#include <memory>
#include <boost/asio.hpp>
#include <iostream>
#include <queue>
#include <boost/bind/bind.hpp>

#include "interfaces.hpp"
#include "server.hpp"
#include "package.hpp"
#include <mutex>

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
    std::queue <Package> pkgs_on_read_;
    std::queue <Package> pkgs_on_write_;
    // Package pkg_;
    // std::queue <Package> pkgs_on_read_;
    // std::queue <Package> pkgs_on_write_;
    enum { header_length = 8 };
    /// Holds an outbound header.
    std::string outbound_header_; // -> write head

    /// Holds the outbound data.
    std::string outbound_data_; // -> write data

    /// Holds an inbound header.
    char inbound_header_[header_length]; //<-read head

    /// Holds the inbound data.
    std::vector<char> inbound_data_; //<- read data

    void start();
    void async_read();
    void on_read(boost::system::error_code error, std::size_t bytes_transferred);
    void async_write();
    void on_write(boost::system::error_code error, std::size_t bytes_transferred);




    void m_async_read() {
        boost::asio::async_read(socket_, boost::asio::buffer(inbound_header_),
            boost::bind(&Session::handle_read_header,
            shared_from_this(), boost::asio::placeholders::error));
    }



    void handle_read_header(const boost::system::error_code& e) {
        if (e) {
            std::cout << "Error: handler read header" << std::endl;
        } else {
            // Determine the length of the serialized data.
            std::istringstream is(std::string(inbound_header_, header_length));
            std::size_t inbound_data_size = 0;
            if (!(is >> std::hex >> inbound_data_size)) {
                // Header doesn't seem to be valid. Inform the caller.
                boost::system::error_code error(boost::asio::error::invalid_argument);
                std::cout << "Error: handler_read_header: Не получается вычитать размер" << std::endl;
                return;
            }
            // Start an asynchronous call to receive the data.
            std::cout << "READ HEAD AND DATASIZE = " << inbound_data_size << std::endl;
            inbound_data_.resize(inbound_data_size);
            boost::asio::async_read(socket_, boost::asio::buffer(inbound_data_),
            boost::bind(&Session::handle_read_data, shared_from_this(),
                boost::asio::placeholders::error));
        }
    }

    void handle_read_data(const boost::system::error_code& e) {
        if (e) {
            std::cout << "Error: handle read data" << std::endl;
        } else {
            Package t;
            // Extract the data structure from the data just received.
            try {
                std::string archive_data(&inbound_data_[0], inbound_data_.size());
                std::istringstream archive_stream(archive_data);
                boost::archive::text_iarchive archive(archive_stream);
                archive >> t;
            } catch (std::exception& e) {
                 // Unable to decode data.
                std::cout << e.what() << std::endl;
                boost::system::error_code error(boost::asio::error::invalid_argument);
                std::cout << "Error: handle_read_data не удалось считать данные" << std::endl;
                return;
            }
            if (!t.finish) {
                std::cout << "I go read second package" << std::endl;
                m_async_read();
            }
            std::cout << t.text << std::endl;
            pkgs_on_read_.push(t);
            if (t.finish) {
                handler_->serve(shared_from_this(), shared_from_this());
            }
        }
    }

    void m_async_write() {
        Package t = pkgs_on_write_.front();
        pkgs_on_write_.pop();
        std::cout << "m_async_write: " << t.voice.size() << std::endl;
        // Serialize the data first so we know how large it is.
        std::ostringstream archive_stream;
        boost::archive::text_oarchive archive(archive_stream);
        archive << t;
        outbound_data_ = archive_stream.str();
        std::cout << outbound_data_.size() << std::endl;
        // Format the header.
        std::ostringstream header_stream;
        header_stream << std::setw(header_length)
        << std::hex << outbound_data_.size();
        if (!header_stream || header_stream.str().size() != header_length) {
            // Something went wrong, inform the caller.
            boost::system::error_code error(boost::asio::error::invalid_argument);
            std::cout << "Error: async_write" << std::endl;
            return;
        }
        outbound_header_ = header_stream.str();

        // Write the serialized data to the socket. We use "gather-write" to send
        // both the header and the data in a single write operation.
        std::vector<boost::asio::const_buffer> buffers;
        buffers.push_back(boost::asio::buffer(outbound_header_));
        buffers.push_back(boost::asio::buffer(outbound_data_));
        boost::asio::write(socket_, buffers);
        // boost::asio::async_write(socket_, buffers, boost::bind(&Session::handle_write, shared_from_this(),
        //     boost::asio::placeholders::error));
    }

    void handle_write(const boost::system::error_code& e) {
        std::cout << "written, good!" << std::endl;
    }




public:

    Session(tcp::socket socket, HandlerSPtr handler);
    std::size_t read(Package & pkg) override;
    std::size_t write(const Package & pkg) override;

    friend class ServerTCP;
};
