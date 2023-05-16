#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <strstream>

#include <libpq-fe.h>


class BasicUser {
public:
    ~BasicUser() = default;

    // Подключиться к бд
    virtual bool connect(const std::string &dbName, const std::string &user,
                         const std::string &password, const std::string &hostAddr,
                         const std::string &port) = 0;

    // ------------------ Table User -----------------------
    // Добавить пользователя
    virtual bool insertUser(const std::string &user_name, const std::string &mail,
                            const std::string &password, const std::string &token) = 0;

    // Изменить данные пользователя
    virtual bool alterUser(const std::string &user_name, const std::string &name,
                           const std::string &mail, const std::string &password,
                           const std::string &token) = 0;

    // Удалить пользователя
    virtual bool deleteUser(const std::string &user_name) = 0;

    // Выбрать данные пользователя
    virtual bool selectUser(const std::string &user_name, std::vector<std::string> &output) = 0;
};


class BasicQuestion {
public:
    ~BasicQuestion() = default;

    // Подключиться к бд
    virtual bool connect(const std::string &dbName, const std::string &user,
                         const std::string &password, const std::string &hostAddr,
                         const std::string &port) = 0;

    // ------------------ Table Question -----------------------
    // Добавить вопрос и ответ добавить возвращение q_id
    virtual std::string insertQuestionAndAnswer(const std::string &user_name,
                                                const std::string &question,
                                                const std::string &answer) = 0;

    // Удалить историю пользователя
    virtual bool deleteUserHistory(const std::string &user_name) = 0;

    // Удалить вопрос и ответы к нему
    virtual bool deleteQuestion(const std::string &question_id) = 0;

    // Получить историю пользователя
    virtual bool getUserHistory(const std::string &user_name, std::string &output) = 0;
};


class BasicAnswer {
public:
    ~BasicAnswer() = default;

    // Подключиться к бд
    virtual bool connect(const std::string &dbName, const std::string &user,
                         const std::string &password, const std::string &hostAddr,
                         const std::string &port) = 0;

    // ------------------ Table Answer -----------------------
    // Добавить ответ
    virtual bool insertAnswer(const std::string &question_id, const std::string &text) = 0;

    // Выбрать 3 ответа на вопрос
    virtual bool selectQuestionAnswers(const std::string &question_id,
                                       std::vector<std::string> &output) = 0;

};


class UserDB : public BasicUser {
public:
    explicit UserDB(): connection_({nullptr,&PQfinish}) {}
    ~UserDB() = default;

    // Подключиться к бд
    bool connect(const std::string &dbName, const std::string &user,
                 const std::string &password, const std::string &hostAddr,
                 const std::string &port) override;


    // ------------------ Table User -----------------------
    // Добавить пользователя
    bool insertUser(const std::string& user_name, const std::string& mail,
                    const std::string& password, const std::string& token) override;

    // Изменить данные пользователя
    bool alterUser(const std::string &user_name, const std::string &name, const std::string &mail,
                   const std::string &password, const std::string &token) override;

    // Удалить пользователя
    bool deleteUser(const std::string &user_name) override;

    // Выбрать данные пользователя
    bool selectUser(const std::string &user_name, std::vector<std::string> &output) override;

private:
    std::unique_ptr<PGconn, decltype(&PQfinish)> connection_;

    bool exists(const std::string &user_name);
};


class QuestionDB : public BasicQuestion {
public:
    explicit QuestionDB(): connection_({nullptr,&PQfinish}) {}
    ~QuestionDB() = default;

    // Подключиться к бд
    bool connect(const std::string &dbName, const std::string &user,
                 const std::string &password, const std::string &hostAddr,
                 const std::string &port) override;

    // ------------------ Table Question -----------------------
    // Добавить вопрос и ответ
    std::string insertQuestionAndAnswer(const std::string &user_name, const std::string &question,
                                 const std::string &answer) override;

    // Удалить историю пользователя
    bool deleteUserHistory(const std::string &user_name) override;

    // Удалить выбранные вопросы и ответы
    bool deleteQuestion(const std::string &question_id) override;

    // Получить последний вопрос пользователя
    bool getUserHistory(const std::string &user_name, std::string &output) override;

private:
    std::unique_ptr<PGconn, decltype(&PQfinish)> connection_;
};


class AnswerDB : public BasicAnswer {
public:
    explicit AnswerDB(): connection_({nullptr,&PQfinish}) {}
    ~AnswerDB() = default;

    // Подключиться к бд
    bool connect(const std::string &dbName, const std::string &user,
                 const std::string &password, const std::string &hostAddr,
                 const std::string &port) override;

    // ------------------ Table Answer -----------------------
    // Добавить ответ
    bool insertAnswer(const std::string &question_id, const std::string &text) override;

    // Выбрать 3 последних ответа на вопрос
    bool selectQuestionAnswers(const std::string &question_id,
                               std::vector<std::string> &output) override;

private:
    std::unique_ptr<PGconn, decltype(&PQfinish)> connection_;
};


/*
 * Проверяю методы на тестовой бд
 */

bool reset_sequence(PGconn* conn, const std::string& table_name);
void set_default();
