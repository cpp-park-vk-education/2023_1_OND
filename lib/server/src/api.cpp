#include "include/api.hpp"

class BoobSphinx : public APISphinx {
public:
    virtual void trans(const std::string& voice_question, std::string& text_question) override {
        // Пустая реализация функции trans
    }
};

std::unique_ptr<APISphinx> createBoobSphinx() {
    return std::make_unique<BoobSphinx>();
}

class BoobFestival : public APIFestival {
public:
    virtual void speak(const std::string & text_answer, std::string & voice_answer) override {
        // Пустая реализация функции speak
    }
};

std::unique_ptr<APIFestival> createBoobFestival() {
    return std::make_unique<BoobFestival>();
}