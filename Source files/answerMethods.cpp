#include "../Header files/database.h"


bool AnswerDB::connect(const std::string &dbName, const std::string &user,
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


// ------------------ Table Answer -----------------------

bool AnswerDB::insertAnswer(const std::string &question_id, const std::string &text) {
    const char* sql = "INSERT INTO public.answer (question_id, answer_text) VALUES ($1, $2)";
    const char* sqlParams[2];

    sqlParams[0] = question_id.c_str();
    sqlParams[1] = text.c_str();

    std::unique_ptr<PGresult, decltype(&PQclear)> result(
            PQexec(connection_.get(), nullptr),
            &PQclear);
    try {
        result.reset(PQexecParams(connection_.get(),
                                  sql,
                                  2,
                                  nullptr,
                                  sqlParams,
                                  nullptr,
                                  nullptr,
                                  0));

        if (PQresultStatus(result.get()) != PGRES_COMMAND_OK) {
            throw std::runtime_error(PQresultErrorMessage(result.get()));
        }
    } catch (const std::exception& e) {
        std::cerr << "Failed to insert data into table 'public.answer': " << e.what() << std::endl;
        return false;
    }

    return true;
}


bool AnswerDB::selectQuestionAnswers(const std::string &question_id,
                                     std::vector<std::string> &output) {
    const char* sql = "SELECT answer_text FROM public.answer "
                      "WHERE question_id = $1 "
                      "ORDER BY answer_time DESC "
                      "LIMIT 3;";
    const char* sqlParams[1] = { question_id.c_str() };
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
        if (PQntuples(result.get()) == 0) {
            std::cerr << "No question or answers" << std::endl;
            return false;
        } else {
            output.clear();
            int nRows = PQntuples(result.get());
            int nCols = PQnfields(result.get());

            std::string outString;
            for (int i = 0; i < nRows; ++i) {
                for (int j = 0; j < nCols; ++j) {
                    outString += PQgetvalue(result.get(), i, j);
                    if (j != nCols - 1)
                        outString += " ";
                }
                output.emplace_back(outString);
                outString.clear();
            }
        }
    }

    return true;
}

