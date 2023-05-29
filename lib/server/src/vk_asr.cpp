#include <nlohmann/json.hpp>

#include "api.hpp"

using json = nlohmann::json;

VkAsr::VkAsr(std::shared_ptr<IClientHTTP> client, const std::string & token): client_(client), token_(token) {}

void VkAsr::trans(const std::string & voice_question, std::string & text_question) {
    std::string url = "https://voice.mcs.mail.ru/asr";
    Header header{{"Content-Type", "audio/wav"}, 
                  {"Authorization", "Bearer " + token_}};
    std::string body = voice_question;
    std::string res;
    client_->post(header, body, url, res);
    
    json resJSON = json::parse(res);
    text_question = resJSON["result"]["texts"][0]["punctuated_text"];
}
