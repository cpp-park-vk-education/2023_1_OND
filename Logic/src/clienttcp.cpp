#include "clienttcp.h"
#include <QDebug>


ClientTCP::ClientTCP(boost::asio::io_context &io_context) : socket(io_context) {}

void ClientTCP::connect(tcp::endpoint ep) {
    socket.connect(ep);
    isConnect = true;
}

std::string ClientTCP::sendAndRecieve(std::string&& msg) {
    //qDebug() << "recieve";
    send(std::move(msg));
     //qDebug() << "send";
    return recieve();
}


void ClientTCP::send(std::string&& msg) {
    if(!isConnect) {
        tcp::endpoint ep(address::from_string("127.0.0.1"), 8001);
        connect(ep);
    }
    
   
    
   // boost::asio::write(socket, msg);
}

std::string ClientTCP::recieve() {
    if(!isConnect) {
        tcp::endpoint ep(address::from_string("127.0.0.1"), 8001);
        connect(ep);
    }
    std::string res;
    
    return res;
}
