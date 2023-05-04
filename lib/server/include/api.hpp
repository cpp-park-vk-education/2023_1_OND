#pragma once 
#include <memory>

class APISphinx {
public:
    virtual ~APISphinx() {}
    virtual void trans() = 0;
};