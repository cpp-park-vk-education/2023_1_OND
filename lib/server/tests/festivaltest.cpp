#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../include/api.hpp"

class MockAPIFestival : public APIFestival {
public:
    MOCK_METHOD2(speak, void(const std::string&, std::string&));
};

// Проверка, что метод speak вызывается ровно один раз
TEST(MockFestivalTest, TestSpeakCallOnce) {
    std::string voice_answer;
    std::string text_answer = "Привет";
    MockAPIFestival mock_api;
    EXPECT_CALL(mock_api, speak(testing::_, testing::_))
        .Times(1);
    APIFestival& api = mock_api;
    api.speak(text_answer, voice_answer);
}

// Проверка, что метод speak правильно преобразует текст в речь
TEST(MockFestivalTest, TestSpeakTextToVoice) {
    std::string voice_answer;
    std::string text_answer = "Привет всем";
    MockAPIFestival mock_api;
    EXPECT_CALL(mock_api, speak(text_answer, testing::_))
        .WillOnce(testing::DoAll(
            testing::SetArgReferee<1>("Привет всем"),
            testing::Return()
        ));
    APIFestival& api = mock_api;
    api.speak(text_answer, voice_answer);
    ASSERT_EQ(voice_answer, "Привет всем");
}

// Проверка, что метод speak не изменяет переменную voice_answer, если text_answer пустой
TEST(MockFestivalTest, TestSpeakEmptyText) {
    std::string voice_answer = "Привет всем";
    std::string text_answer = "";
    MockAPIFestival mock_api;
    EXPECT_CALL(mock_api, speak(text_answer, testing::_))
        .Times(0);
    APIFestival& api = mock_api;
    api.speak(text_answer, voice_answer);
    ASSERT_EQ(voice_answer, "Привет всем");
}