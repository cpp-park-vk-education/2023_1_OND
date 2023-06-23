#include <nlohmann/json.hpp>

#include "api.hpp"

using json = nlohmann::json;

ChatGPT::ChatGPT(std::shared_ptr<IClientHTTP> client,
                 const std::vector<std::string> & tokens): client_(client),
                                                           tokens_(tokens) {}

void ChatGPT::ask(const std::string & token,
                  const std::string & question,
                  std::string & answer) {
    std::string response;
    std::string send_token = token;
    if (send_token.empty() && tokens_.empty()) {
        answer = "Ошибка! У вас не указан токен, и ни одного свободного нет.";
        return;
    } else if (token.empty()) {
        send_token = tokens_[0];
    }
    sendQuestion(send_token, question, response);
    fetchAnswer(response, answer);
}

void ChatGPT::sendQuestion(const std::string & token,
        const std::string & question, std::string & response) {
    std::string url = "https://api.openai.com/v1/chat/completions";
    Header header{{"Content-Type", "application/json"}, 
                  {"Authorization", "Bearer " + token}};
    std::string body = "{\"model\": \"gpt-3.5-turbo\",\"messages\": \
        [{\"role\": \"user\", \"content\": \"" + question + "\"}]}";
    client_->post(header, body, url, response);
}

void ChatGPT::fetchAnswer(const std::string & response, std::string & answer) {
    try {
        json resJSON = json::parse(response);
        if (resJSON.find("error") != resJSON.end()) {
            answer = resJSON["error"];
        } else {
            answer = resJSON["choices"][0]["message"]["content"];
        }
    } catch (std::exception) {
        std::cerr << "Не удалось получить ответ от ChatGPT" << std::endl;
    }
}
