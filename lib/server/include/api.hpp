#pragma once
#include <iostream>
#include <memory>

#include "client_http.hpp"

class APIChatGPT {
public:
    virtual ~APIChatGPT() {}
    virtual void ask(const std::string & token,
                     const std::string & question,
                     std::string & answer) = 0;
};

class ChatGPT: public APIChatGPT {
private:
    std::shared_ptr <IClientHTTP> client_;

    void sendQuestion(const std::string & token, const std::string & question, std::string & response);
    void fetchAnswer(const std::string & response, std::string & answer);

public:
    ChatGPT(std::shared_ptr<IClientHTTP> client);

    void ask(const std::string & token,
             const std::string & question,
             std::string & answer) override;
};


class APISphinx {
public:
    virtual ~APISphinx() {}
    virtual void trans(const std::string & voice_question, std::string & text_question) = 0;
};

class APIFestival {
public:
    virtual ~APIFestival() {}
    virtual void speak(const std::string & text_answer, std::string & voice_answer) = 0;
};
