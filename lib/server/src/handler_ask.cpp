#include <iostream>
#include <chrono>
#include "interfaces.hpp"
#include "package.hpp"
#include "handler.hpp"
#include "gpt_stream.hpp"


Ask::Ask(DatabaseSPtr db, std::shared_ptr<APIChatGPT> gpt,
         std::shared_ptr<IASR> asr,
         const std::vector<std::shared_ptr<ITTS>> & tts,
         const std::string & token_gpt):
            db_(db), gpt_(gpt), asr_(asr), tts_(tts),
            token_gpt_(token_gpt) {}

void Ask::serve(WriterSPtr w, ReaderSPtr r) {
    std::cout << "----ASK START-----" << std::endl;

    Package pkg;
    r->read(pkg);
    std::cout << "Пакет получен" << std::endl;

    std::chrono::_V2::steady_clock::time_point begin;
    std::chrono::_V2::steady_clock::time_point end;
    std::chrono::milliseconds elapsed_ms;


    std::string question_text;
    begin = std::chrono::steady_clock::now();
    asr_->trans(pkg.voice, question_text);
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time: " << elapsed_ms.count() << " ms\n";
    std::cout << "Получен следующий вопрос: " << question_text << std::endl;

    int tts_num = std::stoi(pkg.param["tts"]);
    std::cout << "number tts " << tts_num << std::endl;
    std::string answer;
    if (pkg.param.find("stream") != pkg.param.end()) {
        // В текущей версии приложения
        // такой формат не поддерживается со стороны клиента,
        // и предполагается, что пакет с таким параметром придти не может,
        // поэтому реализация получения ответа от ChatGPT с использованием SSE
        // на стороне сервера написана в качестве эксперимента и в релизной версии
        // продукта не используется, поэтому внимание на качество кода не уделялось.
        ask_gpt(question_text, tts_[tts_num], w, pkg.param["voice"], token_gpt_);
        return;
    }

    std::cout << "Спросим у ChatGPT" << std::endl;
    begin = std::chrono::steady_clock::now();
    gpt_->ask("", question_text, answer);
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time: " << elapsed_ms.count() << " ms\n";
    std::cout << "Ответ от ChatGPT: " << answer << std::endl;


    std::string data;
    begin = std::chrono::steady_clock::now();
    tts_[tts_num]->speak(answer, pkg.param["voice"], data);
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time: " << elapsed_ms.count() << " ms\n";
    std::cout << "получена озвучка: " << data.size() << std::endl;


    Package npkg;
    npkg.finish = true;
    npkg.text = answer;
    npkg.voice = data;
    npkg.param["tts"] = pkg.param["tts"];
    w->write(npkg);
}
