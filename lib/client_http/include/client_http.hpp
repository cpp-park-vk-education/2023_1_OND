#pragma once

class IClientHTTP {
public:
    virtual ~IClientHTTP() {}
    virtual void post() = 0;
};
