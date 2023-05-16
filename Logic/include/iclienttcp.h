#ifndef ICLIENTTCP_H
#define ICLIENTTCP_H

#include <string>

class IClientTCP
{
public:
    virtual void send(std::string&&) = 0;
    virtual std::string recieve() = 0;
    virtual std::string sendAndRecieve(std::string&&) = 0;
    virtual ~IClientTCP() {}
};

#endif // ICLIENTTCP_H
