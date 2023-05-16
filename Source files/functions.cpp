#include "../Header files/database.h"


bool reset_sequence(PGconn* conn, const std::string& table_name) {
    std::string query = "SELECT setval(pg_get_serial_sequence('" + table_name + "', '" + table_name + "_id'), 1, false);";
    PGresult* res = PQexec(conn, query.c_str());
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        std::cerr << "Failed to reset sequence: " << PQresultErrorMessage(res) << std::endl;
        PQclear(res);
        return false;
    }
    PQclear(res);
    return true;
}



void set_default() {
    std::shared_ptr<BasicUser> userDb(new UserDB());
    userDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");

    userDb->deleteUser("");
    PGconn* conn = PQconnectdb("dbname=your_voice user=user password=qwerty host=127.0.0.1 port=5432");

    if (!reset_sequence(conn, "user")) {
        std::cerr << "Failed to reset sequence!" << std::endl;
    }
    if (!reset_sequence(conn, "question")) {
        std::cerr << "Failed to reset sequence!" << std::endl;
    }
    if (!reset_sequence(conn, "answer")) {
        std::cerr << "Failed to reset sequence!" << std::endl;
    }
    userDb->insertUser("user1", "qwerty@mail.ru", "qwerty",
                       "afasdhfojhonc3y498r2403c7rn02382347c502374c5");
    userDb->insertUser("user2", "asdf@mail.ru", "qwerty",
                       "3427c5624c29c4529b6");
    userDb->insertUser("user11", "user11@mail.ru", "qwerty",
                       "3427c5624c29c4529b6");

    std::shared_ptr<BasicQuestion> questionDb(new QuestionDB());
    questionDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");

    questionDb->insertQuestionAndAnswer("user1", "question1 user1", "answer1 question1 user1");
    questionDb->insertQuestionAndAnswer("user1", "question2 user1", "answer1 question2 user1");

    questionDb->insertQuestionAndAnswer("user2", "question1 user2", "answer1 question1 user2");
    questionDb->insertQuestionAndAnswer("user2", "question2 user2", "answer1 question2 user2");


    std::shared_ptr<BasicAnswer> answerDb(new AnswerDB());
    answerDb->connect("your_voice", "user", "qwerty", "127.0.0.1", "5432");

    answerDb->insertAnswer("1", "answer2 question1 user1");
    answerDb->insertAnswer("2", "answer2 question2 user1");
    answerDb->insertAnswer("2", "answer3 question2 user1");

    answerDb->insertAnswer("3", "answer2 question1 user2");
    answerDb->insertAnswer("4", "answer2 question2 user2");

}