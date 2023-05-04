#pragma once
#include <iostream>
#include <vector>

class Database {
public:
    virtual ~Database() {};

    // Подключиться к бд
    virtual bool connect(const std::string &dbName, const std::string &user, const std::string &password, const std::string &hostAddr, const std::string &port) = 0;

    // ------------------ Table User -----------------------
    // Добавить пользователя
    virtual bool insertUser(const std::string &username, const std::string &mail, const std::string &password, const std::string &token) = 0;

    // Изменить данные пользователя
    virtual bool alterUser(const std::string &oldName, const std::string &username, const std::string &mail, const std::string &password,const std::string &token) = 0;

    // Удалить пользователя
    virtual bool deleteUser(const std::string &username) = 0;

    // Выбрать данные пользователя
    virtual bool selectUser(const std::string &username, std::vector<std::string> &output) = 0;


    // ------------------ Table Question -----------------------
    virtual bool insertQuestionAndAnswer(const std::string &user_name, const std::string &question, const std::string &answer) = 0;

    // Удалить историю пользователя
    virtual bool deleteUserHistory(const std::string &user_name, const std::string &date) = 0;

    // Удалить выбранные вопросы
    virtual bool deleteSelectQuestions(const std::string & questions_id) = 0;

    virtual bool getLastQuestion(const std::string & username, std::string & question) = 0;
    
    // ------------------ Table Answer -----------------------
    // Добавить ответ
    virtual bool insertAnswer(const std::string &question_id, const std::string &text) = 0;

    // Выбрать ответы на вопрос
    virtual bool selectQuestionAnswers(const std::string &question_id,std::vector<std::string> &output) = 0;

};
