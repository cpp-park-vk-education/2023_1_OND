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
#include <read_tokens.hpp>

int main() {
    std::vector<std::string> tokens;
    std::string token_vk;
    std::string oauth;
    std::string folder_id;
    std::string key;

    try {
        read_tokens_for_chat_gpt(tokens);
        read_token_for_cloud_voice(token_vk);
        read_token_for_speech_kit(oauth, folder_id);
        read_key_for_text_to_speech(key);
    } catch (std::logic_error & err) {
        std::cerr << err.what() << std::endl;
        return EXIT_FAILURE;
    }

    int port = 8081;

    try {
        std::shared_ptr<ClientHTTP> p = std::make_shared<ClientHTTP>();
        std::shared_ptr<APIChatGPT> gpt = std::make_shared<ChatGPT>(p, tokens);
        DatabaseSPtr db = nullptr;
        std::shared_ptr<IASR> asr = std::make_shared<VkAsr>(p, token_vk);

        std::shared_ptr<ITTS> tts1 = std::make_shared<VkTts>(p, token_vk);
        std::shared_ptr<ITTS> tts2 = std::make_shared<YandexTTS>(p, oauth, folder_id);
        std::shared_ptr<ITTS> tts3 = std::make_shared<TextToSpeech>(p, key);

        boost::asio::io_context io_context;
        ServerTCP s(io_context, port);
        std::shared_ptr <ServeMux>  router = std::make_shared<ServeMux>();
        // tts1 - Cloud Voice (VK)
        // tts2 - SpeechKit (Yandex)
        // tts3 - TextToSpeech (texttospeech.ru)
        std::vector <std::shared_ptr<ITTS>> ttss{tts1, tts2, tts3};
        router->addHandle("ask", std::make_unique<Ask>(db, gpt, asr, ttss, tokens[0]));
        s.setHandler(router);
        io_context.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return EXIT_SUCCESS;
}
