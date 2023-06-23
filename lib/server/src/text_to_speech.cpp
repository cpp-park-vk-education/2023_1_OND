#include <nlohmann/json.hpp>

#include "api.hpp"

using json = nlohmann::json;

TextToSpeech::TextToSpeech(std::shared_ptr<IClientHTTP> client, const std::string & key): client_(client), key_(key) {}

void TextToSpeech::speak(const std::string& text_answer, const std::string & voice, std::string& voice_answer) {
    std::string url = "https://texttospeech.ru/api/v2/synthesize";
    std::cout << key_ << std::endl;
    Header header{{"Content-Type", "application/json"}, 
                  {"Api-Key", key_}};
    std::cout << voice << std::endl;
    std::string body = "{\"code\": \"" + voice + "\", \"text\": \"" + text_answer +
        "\", \"format\": \"wav\"}";
    std::string response;
    client_->post(header, body, url, response);
    try {
        json resJSON = json::parse(response);
        std::string u = resJSON["file"];
        voice_answer = Get(u);
    } catch (std::exception) {
        std::cerr << "Ошибка синтеза речи" << std::endl;
    }
}
