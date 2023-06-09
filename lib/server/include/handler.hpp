#pragma once

#include <vector>
#include "interfaces.hpp"
#include "interface_db.hpp"
#include "api.hpp"

class UserRegistration: public Handler {
private:
    DatabaseSPtr db_;
public:
    UserRegistration(DatabaseSPtr db);
    void serve(WriterSPtr w, ReaderSPtr r) override;
};

class GetUserData: public Handler {
private:
    DatabaseSPtr db_;
public:
    GetUserData(DatabaseSPtr db);
    void serve(WriterSPtr w, ReaderSPtr r) override;
};

class ChangeUserData: public Handler {
private:
    DatabaseSPtr db_;
public:
    ChangeUserData(DatabaseSPtr db);
    void serve(WriterSPtr w, ReaderSPtr r) override;
};

class RemoveUser: public Handler {
private:
    DatabaseSPtr db_;
public:
    RemoveUser(DatabaseSPtr db);
    void serve(WriterSPtr w, ReaderSPtr r) override;
};

class Ask: public Handler {
private:
    DatabaseSPtr db_;
    std::shared_ptr <APIChatGPT> gpt_;
    std::shared_ptr <IASR> asr_;
    std::vector <std::shared_ptr <ITTS>> tts_;
    std::string token_gpt_;

public:
    Ask(DatabaseSPtr db, std::shared_ptr<APIChatGPT> gpt,
        std::shared_ptr<IASR> asr_,
        const std::vector <std::shared_ptr<ITTS>> & tts_,
        const std::string & token_gpt);
    void serve(WriterSPtr w, ReaderSPtr r) override;
};


class GetHistory: public Handler {
private:
    DatabaseSPtr db_;
public:
    GetHistory(DatabaseSPtr db);
    void serve(WriterSPtr w, ReaderSPtr r) override;
};

class RemoveHistory: public Handler {
private:
    DatabaseSPtr db_;
public:
    RemoveHistory(DatabaseSPtr db);
    void serve(WriterSPtr w, ReaderSPtr r) override;
};
