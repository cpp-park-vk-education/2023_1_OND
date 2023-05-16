#include "../Header files/database.h"


bool QuestionDB::connect(const std::string &dbName, const std::string &user,
                     const std::string &password, const std::string &hostAddr,
                     const std::string &port) {
    std::string connectionString = "dbname=" + dbName + " user=" + user + " password=" +
                                   password + " hostaddr=" + hostAddr + " port=" + port;
    const char* connection = connectionString.c_str();
    connection_.reset(PQconnectdb(connection));
    if (PQstatus(connection_.get()) != CONNECTION_OK) {
        std::cerr << "Connection to database failed: " << PQerrorMessage(connection_.get()) <<
                  std::endl;
        return false;
    }
    return true;
}


// ------------------ Table Question -----------------------
std::string QuestionDB::insertQuestionAndAnswer(const std::string &user_name,
                                                const std::string &question,
                                                const std::string &answer) {

    // Get user id
    const char *sql = "SELECT user_id FROM public.user WHERE user_name = $1;";
    const char *sqlParams[1] = { user_name.c_str() };
    int numParams = 1;

    std::unique_ptr<PGresult, decltype(&PQclear)> result(
            PQexecParams(connection_.get(),
                         sql,
                         numParams,
                         nullptr,
                         sqlParams,
                         nullptr,
                         nullptr,
                         0),
            &PQclear);

    if (PQresultStatus(result.get()) != PGRES_TUPLES_OK) {
        std::cerr << "Query failed: " << PQresultErrorMessage(result.get()) << std::endl;
        return "";
    } else {
        if (PQntuples(result.get()) == 0)
            return "";
    }

    std::string user_id = PQgetvalue(result.get(), 0, 0);


    // Insert question
    sql = "INSERT INTO public.question (user_id, question_text) VALUES ($1, $2);";
    const char* sqlParamsInsert[2];
    sqlParamsInsert[0] = user_id.c_str();
    sqlParamsInsert[1] = question.c_str();

    try {
        result.reset(PQexecParams(connection_.get(),
                                  sql,
                                  2,
                                  nullptr,
                                  sqlParamsInsert,
                                  nullptr,
                                  nullptr,
                                  0));

        if (PQresultStatus(result.get()) != PGRES_COMMAND_OK) {
            throw std::runtime_error(PQresultErrorMessage(result.get()));
        }

    } catch (const std::exception& e) {
        std::cerr << "Failed to insert data into table 'public.question': " << e.what() << std::endl;
        return "";
    }

    // Get question id
    sql = "SELECT question_id FROM public.question WHERE user_id = $1 AND question_text = $2;";
    const char* sqlParamsSelect[2];
    sqlParamsSelect[0] = user_id.c_str();
    sqlParamsSelect[1] = question.c_str();

    try {
        result.reset(PQexecParams(connection_.get(),
                                  sql,
                                  2,
                                  nullptr,
                                  sqlParamsSelect,
                                  nullptr,
                                  nullptr,
                                  0));

        if (PQresultStatus(result.get()) != PGRES_TUPLES_OK) {
            throw std::runtime_error(PQerrorMessage(connection_.get()));
        }

    } catch (const std::exception& e) {
        std::cerr << "Failed to execute query to get question_id: " << e.what() << std::endl;
        return "";
    }

    if (PQntuples(result.get()) != 1) {
        std::cerr << "Unexpected result while getting question_id: "
                  << PQntuples(result.get()) << " rows returned" << std::endl;
        return "";
    }

    std::string question_id = PQgetvalue(result.get(), 0, 0);

    // Insert answer
    sql = "INSERT INTO public.answer (question_id, answer_text) VALUES ($1, $2);";
    const char* sqlParamsAnswer[2];
    sqlParamsAnswer[0] = question_id.c_str();
    sqlParamsAnswer[1] = answer.c_str();

    try {
        result.reset(PQexecParams(connection_.get(),
                                  sql,
                                  2,
                                  nullptr,
                                  sqlParamsAnswer,
                                  nullptr,
                                  nullptr,
                                  0));

        if (PQresultStatus(result.get()) != PGRES_COMMAND_OK) {
            throw std::runtime_error(PQresultErrorMessage(result.get()));
        }

    } catch (const std::exception& e) {
        std::cerr << "Failed to insert data into table 'public.answer': " << e.what() << std::endl;
        return "";
    }
    return question_id;
}


bool QuestionDB::deleteUserHistory(const std::string &user_name) {
    // Get user id
    const char *sql = "SELECT user_id FROM public.user WHERE user_name = $1;";
    const char *sqlParams[1] = { user_name.c_str() };
    int numParams = 1;

    std::unique_ptr<PGresult, decltype(&PQclear)> result(
            PQexecParams(connection_.get(),
                         sql,
                         numParams,
                         nullptr,
                         sqlParams,
                         nullptr,
                         nullptr,
                         0),
            &PQclear);

    if (PQresultStatus(result.get()) != PGRES_TUPLES_OK) {
        std::cerr << "Query failed: " << PQresultErrorMessage(result.get()) << std::endl;
        return false;
    } else {
        if (PQntuples(result.get()) == 0)
            return false;
    }

    std::string user_id = PQgetvalue(result.get(), 0, 0);


    // Delete user questions
    sql = "DELETE FROM public.question WHERE user_id = $1";
    const char* sqlParamsDelete[1] = { user_id.c_str() };

    try {
        result.reset(PQexecParams(connection_.get(),
                                  sql,
                                  1,
                                  nullptr,
                                  sqlParamsDelete,
                                  nullptr,
                                  nullptr,
                                  0));

        if (PQresultStatus(result.get()) != PGRES_COMMAND_OK) {
            throw std::runtime_error(PQresultErrorMessage(result.get()));
        }

    } catch (const std::exception& e) {
        std::cerr << "Failed to delete data from table 'public.question': " << e.what() << std::endl;
        return false;
    }
    return true;
}


bool QuestionDB::deleteQuestion(const std::string &question_id) {
    // Check if question exists
    const char* sqlCheck = "SELECT COUNT(*) FROM public.question WHERE question_id = $1";
    const char* sqlParamsCheck[1] = { question_id.c_str() };

    std::unique_ptr<PGresult, decltype(&PQclear)> resultCheck(
            PQexecParams(connection_.get(),
                         sqlCheck,
                         1,
                         nullptr,
                         sqlParamsCheck,
                         nullptr,
                         nullptr,
                         0),
            &PQclear);

    if (PQresultStatus(resultCheck.get()) != PGRES_TUPLES_OK) {
        std::cerr << "Query failed: " << PQresultErrorMessage(resultCheck.get()) << std::endl;
        return false;
    }

    if (std::stoi(PQgetvalue(resultCheck.get(), 0, 0)) == 0) {
        std::cerr << "Question " << question_id << " does not exist in the database" << std::endl;
        return false;
    }

    // Delete the question
    const char* sqlDelete = "DELETE FROM public.question WHERE question_id = $1";
    const char* sqlParamsDelete[1] = { question_id.c_str() };

    std::unique_ptr<PGresult, decltype(&PQclear)> resultDelete(
            PQexecParams(connection_.get(),
                         sqlDelete,
                         1,
                         nullptr,
                         sqlParamsDelete,
                         nullptr,
                         nullptr,
                         0),
            &PQclear);

    if (PQresultStatus(resultDelete.get()) != PGRES_COMMAND_OK) {
        std::cerr << "Failed to delete data from table 'public.question': " << PQresultErrorMessage(resultDelete.get()) << std::endl;
        return false;
    }

    return true;
}


bool QuestionDB::getUserHistory(const std::string &user_name, std::string &output) {
    // Get user id
    const char *sql = "SELECT user_id FROM public.user WHERE user_name = $1;";
    const char *sqlParams[1] = { user_name.c_str() };
    int numParams = 1;

    std::unique_ptr<PGresult, decltype(&PQclear)> result(
            PQexecParams(connection_.get(),
                         sql,
                         numParams,
                         nullptr,
                         sqlParams,
                         nullptr,
                         nullptr,
                         0),
            &PQclear);

    if (PQresultStatus(result.get()) != PGRES_TUPLES_OK) {
        std::cerr << "Query failed: " << PQresultErrorMessage(result.get()) << std::endl;
        return false;
    }
    else if (PQntuples(result.get()) == 0) {
        std::cerr << "Query failed: no user found" << std::endl;
        return false;
    }

    std::string user_id = PQgetvalue(result.get(), 0, 0);

    // Get user history
    sql = "SELECT question_id, question_text FROM public.question "
          "WHERE user_id = $1;";
    const char* sqlParamsSelect[1] = { user_id.c_str() };

    result.reset(PQexecParams(connection_.get(),
                              sql,
                              1,
                              nullptr,
                              sqlParamsSelect,
                              nullptr,
                              nullptr,
                              0));
    if (PQresultStatus(result.get()) != PGRES_TUPLES_OK) {
        std::cerr << "Query failed: " << PQresultErrorMessage(result.get()) << std::endl;
        return false;
    } else {
        if (PQntuples(result.get()) == 0) {
            std::cerr << "Query failed: user has no history" << std::endl;
            return false;
        }
        else {
            int nRows = PQntuples(result.get());
            int nCols = PQnfields(result.get());

            for (int i = 0; i < nRows; ++i) {
                for (int j = 0; j < nCols; ++j) {
                    output.append(PQgetvalue(result.get(), i, j)).append(" ");
                }
            }
        }
    }

    return true;
}
