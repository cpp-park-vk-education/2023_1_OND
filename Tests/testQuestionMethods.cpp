#include "gtest/gtest.h"

#include "../Header files/database.h"


// Подключение к БД
TEST(QuestionMethodsTest, ConnectDB) {
    std::shared_ptr<BasicQuestion> questionDb(new QuestionDB());
    bool result = questionDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    ASSERT_TRUE(result);

}

// Подключение к БД
TEST(QuestionMethodsTest, _ConnectDB) {
    std::shared_ptr<BasicQuestion> questionDb(new QuestionDB());
    bool result = questionDb->connect("your_voice", "user", "asdf", "127.0.0.1", "5432");
    ASSERT_FALSE(result);
}


// Добавление вопроса и ответа
TEST(QuestionMethodsTest, InsertQuestionAndAnswer) {
    std::shared_ptr<BasicQuestion> questionDb(new QuestionDB());
    questionDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    set_default();

    std::string result = questionDb->insertQuestionAndAnswer("user1", "question3 user1",
                                                  "answer1 question3 user1");
    ASSERT_FALSE(result.empty());
}


// Добавление вопроса и ответа несуществующему пользователю
TEST(QuestionMethodsTest, InsertQuestionAndAnswer2NonExistentUser) {
    std::shared_ptr<BasicQuestion> questionDb(new QuestionDB());
    questionDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    set_default();

    std::string result = questionDb->insertQuestionAndAnswer("user3", "question1 user3",
                                                             "answer1 question1 user3");
    ASSERT_TRUE(result.empty());
}


// Удаление истории пользователя
TEST(QuestionMethodsTest, DeleteUserHistory) {
    std::shared_ptr<BasicQuestion> questionDb(new QuestionDB());
    questionDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    set_default();

    bool result = questionDb->deleteUserHistory("user1");
    ASSERT_TRUE(result);
}


// Удаление истории у несуществующего пользователя
TEST(QuestionMethodsTest, DeleteNonExistentUserHistory) {
    std::shared_ptr<BasicQuestion> questionDb(new QuestionDB());
    questionDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    set_default();

    bool result = questionDb->deleteUserHistory("user3");
    ASSERT_FALSE(result);
}


// Удаление истории пользователя с пустой историей
TEST(QuestionMethodsTest, DeleteUserWithClearHistory) {
    std::shared_ptr<BasicQuestion> questionDb(new QuestionDB());
    questionDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    set_default();

    questionDb->deleteUserHistory("user1");
    bool result = questionDb->deleteUserHistory("user1");
    ASSERT_TRUE(result);
}


// Удаление вопроса
TEST(QuestionMethodsTest, DeleteQuestion) {
    std::shared_ptr<BasicQuestion> questionDb(new QuestionDB());
    questionDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    set_default();

    bool result = questionDb->deleteQuestion("1");
    ASSERT_TRUE(result);
}


// Удаление несуществующего вопроса
TEST(QuestionMethodsTest, DeleteNonExistentQuestion) {
    std::shared_ptr<BasicQuestion> questionDb(new QuestionDB());
    questionDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    set_default();

    bool result = questionDb->deleteQuestion("5");
    ASSERT_FALSE(result);
}


// Удаление удаленного вопроса
TEST(QuestionMethodsTest, DeleteDeletedQuestion) {
    std::shared_ptr<BasicQuestion> questionDb(new QuestionDB());
    questionDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    set_default();

    questionDb->deleteQuestion("5");
    bool result = questionDb->deleteQuestion("5");
    ASSERT_FALSE(result);
}


// Выбор истории пользователя
TEST(QuestionMethodsTest, SelectLastQuestion) {
    std::shared_ptr<BasicQuestion> questionDb(new QuestionDB());
    std::string output;
    questionDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    set_default();

    bool result = questionDb->getUserHistory("user1", output);
    ASSERT_TRUE(result);
}


// Выбор истории пользователя и ее проверка
TEST(QuestionMethodsTest, SelectLastQuestionAndCheck) {
    std::shared_ptr<BasicQuestion> questionDb(new QuestionDB());
    std::string output;
    questionDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    set_default();

    questionDb->getUserHistory("user1", output);
    ASSERT_EQ(output, "1 question1 user1 2 question2 user1 ");
}


// Выбор истории у пользователя без истории
TEST(QuestionMethodsTest, SelectLastQuestionFromUserWithNoQuestions) {
    std::shared_ptr<BasicQuestion> questionDb(new QuestionDB());
    std::string output;
    questionDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    set_default();

    ASSERT_FALSE(questionDb->getUserHistory("user11", output));
}


// Выбор последнего вопроса несуществующего пользователя
TEST(QuestionMethodsTest, SelectLastQuestionFromNonExistentUser) {
    std::shared_ptr<BasicQuestion> questionDb(new QuestionDB());
    std::string output;
    questionDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    set_default();

    ASSERT_FALSE(questionDb->getUserHistory("user3", output));
}

