#pragma once
#include <map>

#include "interfaces.hpp"



class ServeMux: public Handler {
private:
    std::map<std::string, std::unique_ptr<Handler>> m_;
public:
    ServeMux();
    void serve(std::shared_ptr<Writer> w, std::shared_ptr<Reader> r) override;
    void addHandle(const std::string & url, std::unique_ptr<Handler> handle);
};
