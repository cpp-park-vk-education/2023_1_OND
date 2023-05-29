#include <nlohmann/json.hpp>

#include "api.hpp"

using json = nlohmann::json;

TextToSpeech::TextToSpeech(std::shared_ptr<IClientHTTP> client, const std::string & key): client_(client), key_(key) {}

void TextToSpeech::speak(const std::string& text_answer, std::string& voice_answer) {
    std::string url = "https://texttospeech.ru/api/v2/synthesize";
    Header header{{"Content-Type", "application/json"}, 
                  {"Api-Key", key_}};
    std::string body = "{\"code\": \"ru-RU001\", \"text\": \"" + text_answer +
        "\", \"format\": \"wav\"}";
    std::string response;
    client_->post(header, body, url, response);
    json resJSON = json::parse(response);
    std::string u = resJSON["file"];
    voice_answer = Get(u);
    // voice_answer.erase(voice_answer.begin(), voice_answer.begin() + 44);
}
