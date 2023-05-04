#include <gtest/gtest.h>
#include "server.hpp"
#include "session.hpp"
#include "serve_mux.hpp"
#include "handler.hpp"

class TestReade {
public:
    void read(const std::string str) {
        
    }
};

class TestWrite: public Writer {
public:
    void write(const std::string str) {
        
    }
};

class TestChatGPT {
public:
    void ask(const std::string );
};