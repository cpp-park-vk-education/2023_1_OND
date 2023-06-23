#include <iostream>
#include "head.hpp"

TEST(ChatGPTTest, AskQuestion) {
    std::shared_ptr<MockClienHTTP> client = std::make_shared<MockClienHTTP>();
    ChatGPT gpt(client, {"token-sdf2"});
    std::string response;
    Header header{{"Authorization", "Bearer token-sdf2"},
                  {"Content-Type", "application/json"}};
    EXPECT_CALL(*client, post(header,
        "{\"model\": \"gpt-3.5-turbo\",\"messages\": [{\"role\": \
         \"user\", \"content\": \"question from the user\"}]}",
        "https://api.openai.com/v1/chat/completions", testing::_)).Times(1);
    std::string answer;
    gpt.ask("token", "question from the user", answer);
}
