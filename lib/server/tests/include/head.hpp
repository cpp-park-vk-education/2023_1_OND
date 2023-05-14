#pragma once
#include <gtest/gtest.h>
#include <iostream>
#include <memory>
#include <vector>
#include <gmock/gmock.h>
#include "server.hpp"
#include "session.hpp"
#include "serve_mux.hpp"
#include "handler.hpp"
#include "api.hpp"
#include "client_http.hpp"

using rows = std::vector<std::string>;

class StubRead: public Reader {
private:
    rows data_;
    std::size_t num_call_;
public:
    StubRead(rows data): data_(data), num_call_(0) {}
    std::size_t read(std::string & str) override {
        str.clear();
        str = data_[num_call_++];
        return str.size();
    }
};

class MockWrite: public Writer {
    rows data_;
public:
    std::size_t write(const std::string & str) override {
        data_.push_back(str);
        return str.size();
    }
    rows getData() {
        return data_;
    }
};

class TestChatGPT: public APIChatGPT {
public:
    void ask(const std::string & token,
             const std::string & question,
             std::string & answer) override;
};

class TestHandle: public Handler {
public:
    void serve(WriterSPtr w, ReaderSPtr r) override {}
};

class MockDatabase: public Database {
public:
    MOCK_METHOD(bool, connect, (const std::string &dbName,
                               const std::string &user,
                               const std::string &password,
                               const std::string &hostAddr,
                               const std::string &port), (override));
    MOCK_METHOD(bool, insertUser, (const std::string &username,
                                   const std::string &mail,
                                   const std::string &password,
                                   const std::string &token), (override));
    MOCK_METHOD(bool, alterUser, (const std::string &oldName,
                                  const std::string &username,
                                  const std::string &mail,
                                  const std::string &password,
                                  const std::string &token), (override));
    MOCK_METHOD(bool, deleteUser, (const std::string &username), (override));
    MOCK_METHOD(bool, selectUser, (const std::string &username,
                                std::vector<std::string> &output), (override));
    MOCK_METHOD(bool, insertQuestionAndAnswer, 
        (const std::string &user_name, const std::string &question,
        const std::string &answer), (override));
    MOCK_METHOD(bool, deleteUserHistory, (const std::string &user_name,
                                        const std::string &date), (override));
    MOCK_METHOD(bool, deleteSelectQuestions, 
        (const std::string & questions_id), (override));
    MOCK_METHOD(bool, getLastQuestion, (const std::string & username, 
                                        std::string & question),
                                        (override));
    MOCK_METHOD(bool, insertAnswer, (const std::string &question_id,
                                     const std::string &text), (override));
    MOCK_METHOD(bool, selectQuestionAnswers, (const std::string &question_id,
        std::vector<std::string> &output), (override));
};

class MockChatGPT: public APIChatGPT {
public:
    MOCK_METHOD(void, ask, (const std::string & token,
                     const std::string & question,
                     std::string & answer), (override));
};

class MockSphinx: public APISphinx {
public:
    MOCK_METHOD(void, trans, (const std::string & voice_question,
                              std::string & text_question), (override));
};

class MockFestival: public APIFestival {
public:
    MOCK_METHOD(void, speak, (const std::string & text_answer,
            std::string & voice_answer), (override));
};

class MockClienHTTP: public IClientHTTP {
public:
    MOCK_METHOD(int, post, (Header & headers,
                            const std::string & body,
                            const std::string & url,
                            std::string & response), (override));
};

using MockWriteSPtr = std::shared_ptr<MockWrite>;
using StubReadSPtr = std::shared_ptr<StubRead>;
using MockDatabaseSPtr = std::shared_ptr<MockDatabase>;
using MockChatGPTSPtr = std::shared_ptr<MockChatGPT>;
using MockSphinxSPtr = std::shared_ptr<MockSphinx>;
using MockFestivalSPtr = std::shared_ptr<MockFestival>;
