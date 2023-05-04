#pragma once 
#include <memory>

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
