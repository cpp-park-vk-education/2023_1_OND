#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../include/api.hpp"

class MockAPISphinx : public APISphinx {
public:
    MOCK_METHOD2(trans, void(const std::string&, std::string&));
};

//случай, когда входным запросом является пустая строка
TEST(MockSphinxTest, TestTransEmpty) {
  std::string voice_question;
  std::string text_question;
  MockAPISphinx mock_api;
  EXPECT_CALL(mock_api, trans(voice_question, testing::_))
      .Times(0);
  APISphinx& api = mock_api;
  api.trans(voice_question, text_question);
  ASSERT_TRUE(text_question.empty());
}

TEST(MockAPISphinxTest, TestTransRussLeng) {
    std::string voice_question = "Какая сегодня погода?";
    std::string text_question;
    MockAPISphinx mock_api;
    EXPECT_CALL(mock_api, trans(voice_question, testing::_))
        .WillOnce(testing::DoAll(
            testing::SetArgReferee<1>("Какая сегодня погода?"),
            testing::Return()
        ));
    APISphinx& api = mock_api;
    api.trans(voice_question, text_question);
    ASSERT_EQ(text_question, "Какая сегодня погода?");
}

TEST(MockAPISphinxTest, TestTransCallOnce) {
  std::string voice_question = "Привет";
  std::string text_question;
  MockAPISphinx mock_api;
  EXPECT_CALL(mock_api, trans(voice_question, testing::_))
      .Times(1);
  APISphinx& api = mock_api;
  api.trans(voice_question, text_question);
}

TEST(MockAPISphinxTest, TestTransLongText) {
  std::string voice_question = "Просто введу сюда длинный запрос в надежде на то, что все упадет, а может и нет, я не знаю";
  std::string text_question;
  MockAPISphinx mock_api;
  EXPECT_CALL(mock_api, trans(voice_question, testing::_))
      .WillOnce(testing::DoAll(
          testing::SetArgReferee<1>("Просто введу сюда длинный запрос в надежде на то, что все упадет или нет"),
          testing::Return()
      ));
  APISphinx& api = mock_api;
  api.trans(voice_question, text_question);
  ASSERT_EQ(text_question, "Просто введу сюда длинный запрос в надежде на то, что все упадет или нет");
}