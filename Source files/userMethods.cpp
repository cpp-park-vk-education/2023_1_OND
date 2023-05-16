#include "../Header files/database.h"


bool UserDB::connect(const std::string &dbName, const std::string &user,
                     const std::string &password, const std::string &hostAddr,
                     const std::string &port) {

    std::string connectionString = "dbname=" + dbName + " user=" + user + " password=" +
                                   password + " hostaddr=" + hostAddr + " port=" + port;
    const char* connection = connectionString.c_str();
    connection_.reset(PQconnectdb(connection));
    if (PQstatus(connection_.get()) != CONNECTION_OK) {
        std::cerr << "Connection to database failed: " << PQerrorMessage(connection_.get()) << std::endl;
        return false;
    }
    return true;
}


// ------------------ Table User -----------------------

bool UserDB::insertUser(const std::string &user_name, const std::string &mail,
                        const std::string &password, const std::string &token) {
    if (user_name.empty() || mail.empty() || password.empty()) {
        std::cerr << "No necessary parameters" << std::endl;
        return false;
    }

    const char* sql = "INSERT INTO public.user (user_name, user_mail, user_password, user_token) "
                       "VALUES ($1, $2, $3, $4)";
    const char* sqlParams[4];

    if (!token.empty()) {
        sqlParams[0] = user_name.c_str();
        sqlParams[1] = mail.c_str();
        sqlParams[2] = password.c_str();
        sqlParams[3] = token.c_str();
    } else {
        sqlParams[0] = user_name.c_str();
        sqlParams[1] = mail.c_str();
        sqlParams[2] = password.c_str();
        sqlParams[3] = nullptr;
    }

    std::unique_ptr<PGresult, decltype(&PQclear)> result(
            PQexec(connection_.get(), nullptr),
            &PQclear);
    try {
        result.reset(PQexecParams(connection_.get(),
                                  sql,
                                  4,
                                  nullptr,
                                  sqlParams,
                                  nullptr,
                                  nullptr,
                                  0));

        if (PQresultStatus(result.get()) != PGRES_COMMAND_OK) {
            throw std::runtime_error(PQresultErrorMessage(result.get()));
        }

    } catch (const std::exception& e) {
        std::cerr << "Failed to insert data into table 'public.user': " << e.what() << std::endl;
        return false;
    }

    return true;
}


bool UserDB::alterUser(const std::string &user_name, const std::string &name, const std::string &mail,
                       const std::string &password, const std::string &token) {
    if (name.empty() || mail.empty() || password.empty()){
        std::cerr << "No necessary parameters" << std::endl;
        return false;
    }
    if (!exists(user_name)) {
        std::cerr << "No user exists" << std::endl;
        return false;
    }

    const char* sql = "UPDATE public.user SET user_mail=$1, user_password=$2, user_token=$3,"
                      " user_name=$4 WHERE user_name=$5";

    const char *sqlParams[5];
    sqlParams[0] = mail.c_str();
    sqlParams[1] = password.c_str();
    sqlParams[2] = token.empty() ? nullptr : token.c_str();
    sqlParams[3] = name.c_str();
    sqlParams[4] = user_name.c_str();

    std::unique_ptr<PGresult, decltype(&PQclear)> result(
            PQexecParams(connection_.get(),
                         sql,
                         5,
                         nullptr,
                         sqlParams,
                         nullptr,
                         nullptr,
                         0),
            &PQclear);

    try {
        if (PQresultStatus(result.get()) != PGRES_COMMAND_OK) {
            throw std::runtime_error(PQresultErrorMessage(result.get()));
        }
    } catch (const std::exception& e) {
        std::cerr << "Failed to update data in table 'public.user': " << e.what() << std::endl;
        return false;
    }
    return true;
}


bool UserDB::deleteUser(const std::string &user_name) {
    const char *sql;
    const char *sqlParams[1];
    int numParams;
    if (!exists(user_name)) {
        sql = "DELETE FROM public.user;";
        numParams = 0;
    } else {
        sql = "DELETE FROM public.user WHERE user_name = $1;";
        sqlParams[0] = user_name.c_str();
        numParams = 1;
    }

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

    try {
        if (PQresultStatus(result.get()) != PGRES_COMMAND_OK) {
            throw std::runtime_error(PQresultErrorMessage(result.get()));
        }
    } catch (const std::exception& e) {
        std::cerr << "Failed to delete data from table 'public.user': " << e.what() << std::endl;
        return false;
    }
    return true;
}


bool UserDB::selectUser(const std::string &user_name, std::vector<std::string> &output) {
    if (!exists(user_name)) {
        std::cerr << "No user exists" << std::endl;
        return false;
    }

    const char *sql = "SELECT user_name, user_mail, user_token FROM public.user WHERE user_name = $1;";
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
        else {
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


bool UserDB::exists(const std::string &user_name) {
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

    return true;
}
