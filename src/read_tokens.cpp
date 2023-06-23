#include <fstream>
#include <iostream>
#include <vector>


void read_tokens_for_chat_gpt(std::vector <std::string> & tokens) {
    std::ifstream fin("../data/chat_gpt.txt");
    if (!fin.is_open()) {
        throw std::logic_error("Не удалось открыть файл с начальными токенами для ChatGPT!");
    }
    std::string token;
    while (fin >> token) {
        tokens.push_back(token);
    }
    fin.close();
}

void read_token_for_cloud_voice(std::string & token) {
    std::ifstream fin("../data/cloud_voice.txt");
    if (!fin.is_open()) {
        throw std::logic_error("Не удалось открыть файл с токеном для Cloud Voice!");
    }
    fin >> token;
    fin.close();
}

void read_token_for_speech_kit(std::string & OAuth, std::string & folder_id) {
    std::ifstream fin("../data/speech_kit.txt");
    if (!fin.is_open()) {
        throw std::logic_error("Не удалось открыть файл с токеном для SpeechKit!");
    }
    fin >> OAuth;
    fin >> folder_id;
    fin.close();
}

void read_key_for_text_to_speech(std::string & key) {
    std::ifstream fin("../data/text_to_speech.txt");
    if (!fin.is_open()) {
        throw std::logic_error("Не удалось открыть файл с ключом для SpeechToText!");
    }
    fin >> key;
    fin.close();
}
