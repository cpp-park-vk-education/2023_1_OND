#include "api.hpp"


ChatGPT::ChatGPT(std::shared_ptr<IClientHTTP> client): client_(client) {}

void ChatGPT::ask(const std::string & token,
                  const std::string & question,
                  std::string & answer) {}

void ChatGPT::sendQuestion(const std::string & token, const std::string & question, std::string & response) {}
void ChatGPT::fetchAnswer(const std::string & response, std::string & answer) {}
