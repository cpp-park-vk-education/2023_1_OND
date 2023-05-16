#include "api.hpp"
#include <pocketsphinx.h>
#include <fstream>
#include <sstream>

CMUSphinx::CMUSphinx(std::shared_ptr<IClientHTTP> client,
                 const std::string & voice_question, std::string & text_question):voice_question_(voice_question),
                                                                                  text_question_(text_question){}

void CMUSphinx::trans(const std::string & voice_question, std::string & text_question){
    // Создаем поток данных из входной строки
    std::stringstream audioStream(voice_question);

    // Создаем временный файл и записываем в него данные из потока
    std::ofstream tempFile("temp.wav", std::ios::binary);
    tempFile << audioStream.rdbuf();
    tempFile.close();

    // Инициализируем CMU-Sphinx
    cmd_ln_t *config = cmd_ln_init(NULL, ps_args(), TRUE, NULL);
    ps_decoder_t *ps = ps_init(config);

    FILE *fh = fopen("temp.wav", "rb");
    if (fh == NULL) {
        return;
    }

    if (ps_start_utt(ps, NULL) < 0) {
        return;
    }

    int16 buf[512];
    size_t nread;
    while (!feof(fh)) {
        nread = fread(buf, 2, sizeof(buf)/2, fh);
        if (ps_process_raw(ps, buf, nread, FALSE, FALSE) < 0) {
            return;
        }
    }

    ps_end_utt(ps);

    text_question = ps_get_hyp(ps, NULL);

    fclose(fh);
    ps_free(ps);
    cmd_ln_free_r(config);
    std::remove("temp.wav");
}
