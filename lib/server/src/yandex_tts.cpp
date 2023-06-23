#include <nlohmann/json.hpp>

#include "api.hpp"

using json = nlohmann::json;

YandexTTS::YandexTTS(std::shared_ptr<IClientHTTP> client,
    const std::string & oauth, const std::string & folder_id):
        client_(client), oauth_(oauth), folder_id_(folder_id) {}

void YandexTTS::speak(const std::string& text_answer, const std::string & voice, std::string& voice_answer) {
    std::string url = "https://iam.api.cloud.yandex.net/iam/v1/tokens";
    std::string res;
    Header head;
    client_->post(head, "{\"yandexPassportOauthToken\":\"" + oauth_ + "\"}", url, res);
    try {
        json resJSON = json::parse(res);
        std::string IAM_token = resJSON["iamToken"];
        Header header{{"Authorization", "Bearer " + IAM_token}};
        url = "https://tts.api.cloud.yandex.net/speech/v1/tts:synthesize";
        url += "?folderId=" + folder_id_;
        url += "&text=" + UrlEncode(text_answer);
        url += "&format=lpcm";
        url += "&sampleRateHertz=48000";
        url += "&voice=" + UrlEncode(voice);
        std::string response;
        client_->post(header, "", url, response);
        voice_answer = response;
    } catch (std::exception & e) {
        std::cerr << "Ошибка синтеза речи speechKit: " << e.what() << std::endl;
    }
}
