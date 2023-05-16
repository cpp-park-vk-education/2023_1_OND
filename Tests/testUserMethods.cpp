#include <gtest/gtest.h>

#include "../Header files/database.h"


// Подключение к БД
TEST(UserMethodsTest, ConnectDB) {
    std::shared_ptr<BasicUser> userDb(new UserDB());
    bool result = userDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    ASSERT_TRUE(result);

}

// Подключение к БД
TEST(UserMethodsTest, _ConnectDB) {
    std::shared_ptr<BasicUser> userDb(new UserDB());
    bool result = userDb->connect("your_voice", "user", "asdf", "127.0.0.1", "5432");
    ASSERT_FALSE(result);
}


// ---------------------------- Testing User -----------------------------

// Добавление пользователя
TEST(UserMethodsTest, InsertUser) {
    std::shared_ptr<BasicUser> userDb(new UserDB());
    userDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    set_default();

    bool result = userDb->insertUser("user3", "wqer@mail.ru", "qwerty", "afasdhfojhonc3y498r2403c7rn02382347c502374c5");
    ASSERT_TRUE(result);
}

// Добавление пользователя без токена
TEST(UserMethodsTest, InsertUserWithoutToken) {
    std::shared_ptr<BasicUser> userDb(new UserDB());
    userDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    set_default();

    bool result = userDb->insertUser("user3", "wqer@mail.ru", "qwerty", "");
    ASSERT_TRUE(result);
}


// Добавление пользователя без пароля
TEST(UserMethodsTest, InsertUserWithoutPassword) {
    std::shared_ptr<BasicUser> userDb(new UserDB());
    userDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    set_default();

    bool result = userDb->insertUser("user3", "wqer@mail.ru", "", "");
    ASSERT_FALSE(result);
}


// Добавление пользователя без почты
TEST(UserMethodsTest, InsertUserWithoutMail) {
    std::shared_ptr<BasicUser> userDb(new UserDB());
    userDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    set_default();

    bool result = userDb->insertUser("user3", "", "qwerty", "");
    ASSERT_FALSE(result);
}


// Добавление пользователя без user_name
TEST(UserMethodsTest, InsertUserWithoutName) {
    std::shared_ptr<BasicUser> userDb(new UserDB());
    userDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    set_default();

    bool result = userDb->insertUser("", "wqer@mail.ru", "qwerty", "");
    ASSERT_FALSE(result);
}


// Добавление пользователя без заполнения обязательных данных
TEST(UserMethodsTest, InsertUserWithoutALL) {
    std::shared_ptr<BasicUser> userDb(new UserDB());
    userDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    set_default();

    bool result = userDb->insertUser("", "", "", "931246hc97164bcv987123465bvcf912");
    ASSERT_FALSE(result);
}


// Добавления пользователя с занятным именем
TEST(UserMethodsTest, InsertExistingUser_NAME) {
    std::shared_ptr<BasicUser> userDb(new UserDB());
    userDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    set_default();

    bool result = userDb->insertUser("user1", "qwe@mail.ru", "qwerty",
                                     "afasdhfojhonc3y498r2403c7rn02382347c502374c5");
    ASSERT_FALSE(result);
}


// Добавления пользователя с занятой почтой
TEST(UserMethodsTest, InsertExistingUser_MAIL) {
    std::shared_ptr<BasicUser> userDb(new UserDB());
    userDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    set_default();

    bool result = userDb->insertUser("user3", "qwerty@mail.ru", "qwerty",
                                     "afasdhfojhonc3y498r2403c7rn02382347c502374c5");
    ASSERT_FALSE(result);
}


// Добавления пользователя с занятой почтой и user_name
TEST(UserMethodsTest, InsertExistingUser_MailAndName) {
    std::shared_ptr<BasicUser> userDb(new UserDB());
    userDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    set_default();

    bool result = userDb->insertUser("user1", "qwerty@mail.ru", "qwerty",
                                     "afasdhfojhonc3y498r2403c7rn02382347c502374c5");
    ASSERT_FALSE(result);
}


// Удаление пользователя
TEST(UserMethodsTest, DeleteUser) {
    std::shared_ptr<BasicUser> userDb(new UserDB());
    userDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    set_default();

    bool result = userDb->deleteUser("user1");
    ASSERT_TRUE(result);
}


// Удаление несуществующего пользователя
TEST(UserMethodsTest, DoubleDeletingUser) {
    std::shared_ptr<BasicUser> userDb(new UserDB());
    userDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    set_default();

    bool result = userDb->deleteUser("user3");
    ASSERT_TRUE(result);
}


// Изменение данных о пользователе
TEST(UserMethodsTest, AlterUser) {
    std::shared_ptr<BasicUser> userDb(new UserDB());
    userDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    set_default();

    bool result = userDb->alterUser("user1", "user3", "fdas@mail.ru", "qwerty",
                                    "afasdhfojhonc3y498r2403c7rn02382347c502374c5");
    ASSERT_TRUE(result);
}


// Изменение данных о пользователе и их проверка
TEST(UserMethodsTest, AlterUserAndCheck) {
    std::shared_ptr<BasicUser> userDb(new UserDB());
    std::vector<std::string> output;
    userDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    set_default();

    bool result = userDb->alterUser("user1", "user3", "fdas@mail.ru", "qwerty",
                                    "afasdhfojhonc3y498r2403c7rn02382347c502374c5");
    ASSERT_TRUE(result);

    userDb->selectUser("user3", output);
    ASSERT_EQ(output[0], "user3 fdas@mail.ru afasdhfojhonc3y498r2403c7rn02382347c502374c5");
}


// Изменение данных о пользователе без передачи нужных данных (имени)
TEST(UserMethodsTest, AlterUserWithoutName) {
    std::shared_ptr<BasicUser> userDb(new UserDB());
    userDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    set_default();

    bool result = userDb->alterUser("user1", "", "fdas@mail.ru", "qwerty",
                                    "afasdhfojhonc3y498r2403c7rn02382347c502374c5");
    ASSERT_FALSE(result);
}


// Изменение данных о пользователе без передачи нужных данных (почты)
TEST(UserMethodsTest, AlterUserWithoutMail) {
    std::shared_ptr<BasicUser> userDb(new UserDB());
    userDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    set_default();

    bool result = userDb->alterUser("user1", "user3", "", "qwerty",
                                    "afasdhfojhonc3y498r2403c7rn02382347c502374c5");
    ASSERT_FALSE(result);
}


// Изменение данных о пользователе без передачи нужных данных (пароль)
TEST(UserMethodsTest, AlterUserWithoutPassword) {
    std::shared_ptr<BasicUser> userDb(new UserDB());
    userDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    set_default();

    bool result = userDb->alterUser("user1", "user3", "fdas@mail.ru", "",
                                    "afasdhfojhonc3y498r2403c7rn02382347c502374c5");
    ASSERT_FALSE(result);
}


// Изменение данных о пользователе без передачи нужных данных
TEST(UserMethodsTest, AlterUserWithoutAll) {
    std::shared_ptr<BasicUser> userDb(new UserDB());
    userDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    set_default();

    bool result = userDb->alterUser("user1", "", "", "", "afasdhfojhonc3y498r2403c7rn02382347c502374c5");
    ASSERT_FALSE(result);
}


// Изменение данных о пользоветеле с несуществующем name
TEST(UserMethodsTest, AlterNonExistentUser_NAME) {
    std::shared_ptr<BasicUser> userDb(new UserDB());
    userDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    set_default();

    bool result = userDb->alterUser("user3", "user4", "fdas@mail.ru", "qwerty",
                                    "afasdhfojhonc3y498r2403c7rn02382347c502374c5");
    ASSERT_FALSE(result);
}


// Изменение данных пользователя на уже занятый user_name
TEST(UserMethodsTest, AlterUser_OccupiedName) {
    std::shared_ptr<BasicUser> userDb(new UserDB());
    userDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    set_default();

    bool result = userDb->alterUser("user1", "user2", "fdas@mail.ru", "qwerty",
                                    "afasdhfojhonc3y498r2403c7rn02382347c502374c5");
    ASSERT_FALSE(result);
}


// Изменение данных пользователя на уже занятую почту
TEST(UserMethodsTest, AlterUser_OccupiedMail) {
    std::shared_ptr<BasicUser> userDb(new UserDB());
    userDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    set_default();

    bool result = userDb->alterUser("user1", "user3", "asdf@mail.ru", "qwerty",
                                    "afasdhfojhonc3y498r2403c7rn02382347c502374c5");
    ASSERT_FALSE(result);
}


// Получить данные о пользователе
TEST(UserMethodsTest, SelectUser) {
    std::shared_ptr<BasicUser> userDb(new UserDB());
    std::vector<std::string> output;
    userDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    set_default();

    bool result = userDb->selectUser("user1", output);
    ASSERT_TRUE(result);
}


// Получить данные о пользователе и проверить их
TEST(UserMethodsTest, SelectUserAndCheck) {
    std::shared_ptr<BasicUser> userDb(new UserDB());
    std::vector<std::string> output;
    userDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    set_default();

    bool result = userDb->selectUser("user1", output);
    ASSERT_TRUE(result);

    ASSERT_EQ(output[0], "user1 qwerty@mail.ru afasdhfojhonc3y498r2403c7rn02382347c502374c5");
}


// Получить данные о несуществующем пользователе
TEST(UserMethodsTest, SelectNonExistentUser) {
    std::shared_ptr<BasicUser> userDb(new UserDB());
    std::vector<std::string> output;
    userDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");
    set_default();

    bool result = userDb->selectUser("user3", output);
    ASSERT_FALSE(result);
}
