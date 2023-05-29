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
    std::vector <std::string> tokens_;

    void sendQuestion(const std::string & token, const std::string & question, std::string & response);
    void fetchAnswer(const std::string & response, std::string & answer);

public:
    ChatGPT(std::shared_ptr<IClientHTTP> client,
            const std::vector <std::string> & tokens);

    void ask(const std::string & token,
             const std::string & question,
             std::string & answer) override;
};

class IASR {
public:
    virtual ~IASR() {}
    virtual void trans(const std::string & voice_question, std::string & text_question) = 0;
};

class ITTS {
public:
    virtual ~ITTS() {}
    virtual void speak(const std::string & text_answer, std::string & voice_answer) = 0;
};

class TextToSpeech: public ITTS {
private:
    std::shared_ptr <IClientHTTP> client_;
    std::string key_;

public:
    TextToSpeech(std::shared_ptr<IClientHTTP> client, const std::string & key);
    void speak(const std::string & text_answer, std::string & voice_answer) override;
};



class VkAsr: public IASR {
public:
    std::shared_ptr <IClientHTTP> client_;
    std::string token_;

public:
    VkAsr(std::shared_ptr<IClientHTTP> client, const std::string & token);

    void trans(const std::string & voice_question, std::string & text_question) override;
};


class YandexTTS: public ITTS {
private:
    std::shared_ptr <IClientHTTP> client_;
    std::string oauth_;
    std::string folder_id_;

public:
    YandexTTS(std::shared_ptr<IClientHTTP> client, 
        const std::string & oauth, const std::string & folder_id);
    void speak(const std::string & text_answer, std::string & voice_answer) override;
};


class VkTts: public ITTS {
private:
    std::shared_ptr <IClientHTTP> client_;
    std::string token_;

public:
    VkTts(const std::shared_ptr<IClientHTTP> client, const std::string & token);
    void speak(const std::string & text_answer, std::string & voice_answer) override;
};
