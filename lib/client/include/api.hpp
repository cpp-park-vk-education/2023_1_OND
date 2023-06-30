#pragma once
#include <iostream>

/*class APIChatGPT {
public:
    virtual ~APIChatGPT() {}
    virtual void ask(const std::string & token,
                     const std::string & question,
                     std::string & answer) = 0;
};*/

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