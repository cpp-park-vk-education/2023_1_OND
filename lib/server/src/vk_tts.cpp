#include <nlohmann/json.hpp>

#include "api.hpp"

using json = nlohmann::json;

VkTts::VkTts(std::shared_ptr<IClientHTTP> client, const std::string & token): client_(client), token_(token) {}

void VkTts::speak(const std::string& text_answer, const std::string & voice, std::string& voice_answer) {
    std::string url = "https://voice.mcs.mail.ru/tts?model_name=" + voice;
    Header header{{"Authorization", "Bearer " + token_},
                  {"Content-Type", "text/plain"}};
    std::string response;
    client_->post(header, text_answer, url, response);
    voice_answer = response;
}