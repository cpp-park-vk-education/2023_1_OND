#include "session.hpp"
#include "package.hpp"

Session::Session(tcp::socket socket, std::shared_ptr <Handler> handler):
    socket_(std::move(socket)), handler_(handler) {}

void Session::start() {
    std::cout << "New connection" << std::endl;
    async_read();
}

std::size_t Session::read(Package & pkg) {
    pkg = pkgs_on_read_.front();
    pkgs_on_read_.pop();
    return 0;
}

std::size_t Session::write(const Package & pkg) {
        pkgs_on_write_.push(pkg);
        async_write();
        return 0;
}

void Session::async_read() {
    boost::asio::async_read(socket_, boost::asio::buffer(inbound_header_),
            boost::bind(&Session::handle_read_header,
            shared_from_this(), boost::asio::placeholders::error));
}

void Session::async_write() {
    Package t = pkgs_on_write_.front();
        pkgs_on_write_.pop();
        std::cout << "async_write only voice bytes: " << t.voice.size() << std::endl;

        std::ostringstream archive_stream;
        boost::archive::text_oarchive archive(archive_stream);
        archive << t;
        outbound_data_ = archive_stream.str();
        std::cout << "async_write bytes: " << outbound_data_.size() << std::endl;

        std::ostringstream header_stream;
        header_stream << std::setw(header_length)
        << std::hex << outbound_data_.size();
        if (!header_stream || header_stream.str().size() != header_length) {
            boost::system::error_code error(boost::asio::error::invalid_argument);
            std::cerr << "Error: async_write" << std::endl;
            return;
        }

        outbound_header_ = header_stream.str();
        std::vector<boost::asio::const_buffer> buffers;
        buffers.push_back(boost::asio::buffer(outbound_header_));
        buffers.push_back(boost::asio::buffer(outbound_data_));
        std::size_t n = boost::asio::write(socket_, buffers);
        std::cout << "realy write bytes: " << n << std::endl;
}

void Session::handle_read_header(const boost::system::error_code& e) {
    if (e) {
        std::cerr << "Error: handler read header" << std::endl;
    } else {
        std::istringstream is(std::string(inbound_header_, header_length));
        std::size_t inbound_data_size = 0;
        if (!(is >> std::hex >> inbound_data_size)) {
            boost::system::error_code error(boost::asio::error::invalid_argument);
            std::cerr << "Error: handler_read_header: Не получается вычитать размер" << std::endl;
            return;
        }
        std::cout << "READ HEAD AND DATASIZE = " << inbound_data_size << std::endl;
        inbound_data_.resize(inbound_data_size);
        boost::asio::async_read(socket_, boost::asio::buffer(inbound_data_),
        boost::bind(&Session::handle_read_data, shared_from_this(),
            boost::asio::placeholders::error));
    }
}

void Session::handle_read_data(const boost::system::error_code& e) {
    if (e) {
        std::cerr << "Error: handle read data" << std::endl;
    } else {
        Package t;
        try {
            std::string archive_data(&inbound_data_[0], inbound_data_.size());
            std::istringstream archive_stream(archive_data);
            boost::archive::text_iarchive archive(archive_stream);
            archive >> t;
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            boost::system::error_code error(boost::asio::error::invalid_argument);
            std::cerr << "Error: handle_read_data не удалось считать данные" << std::endl;
            return;
        }
        if (!t.finish) {
            std::cout << "go read next package" << std::endl;
            async_read();
        }
        std::cout << t.text << std::endl;
        pkgs_on_read_.push(t);
        if (t.finish) {
            handler_->serve(shared_from_this(), shared_from_this());
        }
    }
}
