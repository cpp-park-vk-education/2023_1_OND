#include <iostream>
#include <memory>
#include "head.hpp"

class TestHandler1: public Handler {
public:
    void serve(WriterSPtr w, ReaderSPtr r) override {
        std::string str;
        r->read(str);
        w->write("Handler1: " + str);
    }
};

class TestHandler2: public Handler {
public:
    void serve(WriterSPtr w, ReaderSPtr r) override {
        std::string str;
        r->read(str);
        w->write("Handler2: " + str);
    }
};

TEST(ServeMuxTest, ServeNecessaryHandler) {
    ServeMux router;
    router.addHandle("one", std::make_unique<TestHandler1>());
    router.addHandle("two", std::make_unique<TestHandler2>());

    StubReadSPtr reader = std::make_shared<StubRead>(rows{"two", "body"});
    MockWriteSPtr writer = std::make_shared<MockWrite>();

    router.serve(writer, reader);

    EXPECT_EQ(writer->getData(), rows{"Handler2: body"});
}

TEST(ServeMuxTest, ServeNotExistsHandler) {
    ServeMux router;
    router.addHandle("one", std::make_unique<TestHandler1>());
    router.addHandle("two", std::make_unique<TestHandler2>());

    StubReadSPtr reader = std::make_shared<StubRead>(rows{"three", "body"});
    MockWriteSPtr writer = std::make_shared<MockWrite>();

    router.serve(writer, reader);

    EXPECT_EQ(writer->getData(), rows{"target not found"});
}
