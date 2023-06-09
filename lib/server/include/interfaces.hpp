#pragma once
#include <memory>
#include "package.hpp"

class Writer {
public:
    virtual ~Writer() {}
    virtual std::size_t write(const Package & pkg) = 0;
};

class Reader {
public:
    virtual ~Reader() {}
    virtual std::size_t read(Package & r) = 0;
};

using WriterSPtr = std::shared_ptr<Writer>;
using ReaderSPtr = std::shared_ptr<Reader>;

class Handler {
public:
    virtual ~Handler() {}
    virtual void serve(WriterSPtr w,
                       ReaderSPtr r) = 0;
};

using HandlerSPtr = std::shared_ptr<Handler>;
