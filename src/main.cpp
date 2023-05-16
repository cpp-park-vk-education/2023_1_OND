#include <iostream>
#include "server.hpp"
#include "interfaces.hpp"
#include "session.hpp"
#include "serve_mux.hpp"
#include "handler.hpp"
#include "interface_db.hpp"
#include "client_http.hpp"
#include <memory>
#include <fstream>

int main() {
    std::ifstream fin("../data/tokens.txt");
    if (!fin.is_open()) {
        std::cerr << "Не удалось открыть файл с начальными токенами!" << std::endl;
        return EXIT_FAILURE;
    }
    std::string token;
    std::vector <std::string> tokens;
    while (fin >> token) {
        tokens.push_back(token);
    }
    try {
        std::shared_ptr<ClientHTTP> p = std::make_shared<ClientHTTP>();
        std::shared_ptr<APIChatGPT> gpt = std::make_shared<ChatGPT>(p, tokens);
        DatabaseSPtr db = nullptr;
        std::shared_ptr<APISphinx> sphinx = std::make_shared<Sphinx>();
        boost::asio::io_context io_context;
        ServerTCP s(io_context, 8001);
        std::shared_ptr <ServeMux>  router = std::make_shared<ServeMux>();
        router->addHandle("ask", std::make_unique<Ask>(db, gpt, sphinx, nullptr));
        s.setHandler(router);
        io_context.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return EXIT_SUCCESS;
}
