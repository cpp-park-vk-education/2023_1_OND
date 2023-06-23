#ifndef CLIENTTCP_H
#define CLIENTTCP_H

#include "iclienttcp.h"
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using boost::asio::ip::address;
using namespace boost::asio;

class ClientTCP : public IClientTCP
{
public:
    ClientTCP(boost::asio::io_context&);
    ClientTCP(ClientTCP&&) = default;
    void connect(tcp::endpoint);
    std::string sendAndRecieve(std::string&&) override;
    void send(std::string&&) override;
    std::string recieve() override;
    ~ClientTCP() = default;
private:
    tcp::socket socket;
    bool isConnect;
    enum { headerLength = 8 };

};

#endif // CLIENTTCP_H
