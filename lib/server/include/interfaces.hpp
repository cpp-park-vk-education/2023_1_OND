#pragma once
#include <memory>

class Writer {
public:
    virtual ~Writer() {}
    virtual std::size_t write(const std::string & message) = 0;
};

class Reader {
public:
    virtual ~Reader() {}
    virtual std::size_t read(std::string & r) = 0;
};

class Handler {
public:
    virtual ~Handler() {}
    virtual void serve(std::shared_ptr <Writer> w,
                       std::shared_ptr <Reader> r) = 0;
};


using WriterSPtr = std::shared_ptr<Writer>;
using ReaderSPtr = std::shared_ptr<Reader>;
using HandlerSPtr = std::shared_ptr<Handler>;