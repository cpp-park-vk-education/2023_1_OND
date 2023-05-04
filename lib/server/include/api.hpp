#pragma once
#include <iostream>

class APIChatGPT {
public:
    virtual ~APIChatGPT() {}
    virtual void ask(const std::string & token,
                     const std::string & question,
                     std::string & answer) = 0;
};

