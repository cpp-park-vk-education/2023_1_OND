#include "gtest/gtest.h"

#include "../Header files/database.h"

// Подключение к БД
TEST(AnswerMethodsTest, ConnectDB) {
    std::shared_ptr<BasicAnswer> answerDb(new AnswerDB());
    bool result = answerDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    ASSERT_TRUE(result);

}

// Подключение к БД
TEST(AnswerMethodsTest, _ConnectDB) {
    std::shared_ptr<BasicAnswer> answerDb(new AnswerDB());
    bool result = answerDb->connect("your_voice", "user", "asdf", "127.0.0.1", "5432");
    ASSERT_FALSE(result);
}


// Добавление ответа
TEST(AnswerMethodsTest, InsertAnswer) {
    std::shared_ptr<BasicAnswer> answerDb(new AnswerDB());
    answerDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    set_default();

    bool result = answerDb->insertAnswer("1", "answer3 question1 user1");
    ASSERT_TRUE(result);
}


// Добавление ответа и проверка
TEST(AnswerMethodsTest, InsertAnswerAndCheck) {
    std::shared_ptr<BasicAnswer> answerDb(new AnswerDB());
    std::vector<std::string> output;
    answerDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    set_default();

    answerDb->insertAnswer("1", "answer3 question1 user1");

    answerDb->selectQuestionAnswers("1", output);
    ASSERT_EQ(output.size(), 3);
    ASSERT_EQ(output[0], "answer3 question1 user1");
    ASSERT_EQ(output[1], "answer2 question1 user1");
    ASSERT_EQ(output[2], "answer1 question1 user1");
}


// Добавление ответа на удаленный вопрос
TEST(AnswerMethodsTest, InsertAnswer2NonExistentQuestion) {
    std::shared_ptr<BasicAnswer> answerDb(new AnswerDB());
    answerDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    set_default();

    bool result = answerDb->insertAnswer("5", "answer1 question3 user1");
    ASSERT_FALSE(result);
}


// Выбрать ответы на вопрос
TEST(AnswerMethodsTest, SelectAnswers) {
    std::shared_ptr<BasicAnswer> answerDb(new AnswerDB());
    std::vector<std::string> output;
    answerDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    set_default();

    bool result = answerDb->selectQuestionAnswers("1", output);
    ASSERT_TRUE(result);
}


// Выбрать ответы на вопрос и проверить их
TEST(AnswerMethodsTest, Select3AnswersAndCheck) {
    std::shared_ptr<BasicAnswer> answerDb(new AnswerDB());
    std::vector<std::string> output;
    answerDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    set_default();

    bool result = answerDb->selectQuestionAnswers("2", output);
    ASSERT_TRUE(result);

    ASSERT_EQ(output.size(), 3);
    ASSERT_EQ(output[2], "answer1 question2 user1");
    ASSERT_EQ(output[1], "answer2 question2 user1");
    ASSERT_EQ(output[0], "answer3 question2 user1");
}


// Выбрать ответы на удаленный вопрос
TEST(AnswerMethodsTest, SelectAnswersNonExistentQuestion) {
    std::shared_ptr<BasicAnswer> answerDb(new AnswerDB());
    std::vector<std::string> output;
    answerDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    set_default();

    bool result = answerDb->selectQuestionAnswers("5", output);
    ASSERT_FALSE(result);
}
