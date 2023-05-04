#pragma once

#include "interfaces.hpp"
#include "interface_db.hpp"
#include "api.hpp"

class UserRegistration: public Handler {
private:
    std::shared_ptr <Database> db_;
public:
    UserRegistration(std::shared_ptr<Database> db);
    void serve(std::shared_ptr <Writer> w, std::shared_ptr<Reader> r) override;
};

class GetUserData: public Handler {
private:
    std::shared_ptr <Database> db_;
public:
    GetUserData(std::shared_ptr<Database> db);
    void serve(std::shared_ptr <Writer> w, std::shared_ptr<Reader> r) override;
};

class ChangeUserData: public Handler {
private:
    std::shared_ptr <Database> db_;
public:
    ChangeUserData(std::shared_ptr<Database> db);
    void serve(std::shared_ptr <Writer> w, std::shared_ptr<Reader> r) override;
};

class RemoveUser: public Handler {
private:
    std::shared_ptr <Database> db_;
public:
    RemoveUser(std::shared_ptr<Database> db);
    void serve(std::shared_ptr <Writer> w, std::shared_ptr<Reader> r) override;
};

class Ask: public Handler {
private:
    std::shared_ptr <Database> db_;
    std::shared_ptr <APIChatGPT> gpt_;
public:
    Ask(std::shared_ptr<Database> db, std::shared_ptr<APIChatGPT> gpt);
    void serve(std::shared_ptr <Writer> w, std::shared_ptr<Reader> r) override;
};


class GetHistory: public Handler {
private:
    std::shared_ptr <Database> db_;
public:
    GetHistory(std::shared_ptr<Database> db);
    void serve(std::shared_ptr <Writer> w, std::shared_ptr<Reader> r) override;
};

class RemoveHistory: public Handler {
private:
    std::shared_ptr <Database> db_;
public:
    RemoveHistory(std::shared_ptr<Database> db);
    void serve(std::shared_ptr <Writer> w, std::shared_ptr<Reader> r) override;
};
