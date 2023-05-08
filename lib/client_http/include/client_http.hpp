#pragma once
#include <map>

using Header = std::map<std::string, std::string>;

class IClientHTTP {
public:
    virtual ~IClientHTTP() {}
    virtual int post(const Header & headers, const std::string & body, const std::string & url, std::string & response) = 0;
};

class ClientHTTP: public IClientHTTP {
public:
    int post(const Header & headers, const std::string & body, const std::string & url, std::string & response) override;
};
