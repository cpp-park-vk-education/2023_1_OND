#pragma once
#include <map>

#include "interfaces.hpp"



class ServeMux: public Handler {
private:
    std::map<std::string, std::unique_ptr<Handler>> m_;
public:
    ServeMux();
    void serve(WriterSPtr w, ReaderSPtr r) override;
    void addHandle(const std::string & url, HandlerSPtr handle);
};
