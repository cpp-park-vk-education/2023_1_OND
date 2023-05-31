#include "handler.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>
#include "package.hpp"


Ask::Ask(DatabaseSPtr db, std::shared_ptr<APIChatGPT> gpt,
         std::shared_ptr<IASR> asr,
         const std::vector<std::shared_ptr<ITTS>> & tts):
            db_(db), gpt_(gpt), asr_(asr), tts_(tts) {}

void Ask::serve(WriterSPtr w, ReaderSPtr r) {
   std::cout << "----ASK START-----" << std::endl;

   Package pkg;
   r->read(pkg);
   // std::cout << "ITAK" << question_voice << std::endl;
   std::ofstream out("question.wav");
   out.write(pkg.voice.c_str(), pkg.voice.size());
   std::cout << pkg.voice.size() << std::endl;

   std::cout << "Вопрос сохранён" << std::endl;

   std::string question_text;
   auto begin = std::chrono::steady_clock::now();
   asr_->trans(pkg.voice, question_text);
   auto end = std::chrono::steady_clock::now();
   auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
   std::cout << "The time: " << elapsed_ms.count() << " ms\n";
   std::cout << "Получен следующий вопрос: " << question_text << std::endl;
   
   std::string answer = "Самая большая ягода в мире - это ягода джекфрута";

   std::cout << "Спросим у ChatGPT" << std::endl;
   begin = std::chrono::steady_clock::now();
   gpt_->ask("", question_text, answer);
   end = std::chrono::steady_clock::now();
   std::cout << "Ответ от ChatGPT: " << answer << std::endl;
   elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
   std::cout << "The time: " << elapsed_ms.count() << " ms\n";
   std::string data;

   begin = std::chrono::steady_clock::now();
   // std::stringstream SS;
   // SS << answer;

   // int kk = 100;

   // answer.clear();
   // for (int i = 0;;++i) {
   //    std::string s;
   //    if (SS >> s) {
   //       answer += s + " ";
   //    } else {if (!answer.empty()) {
   //       std::string cd;
   //       std::cout << "last: " << answer << std::endl;
   //       festival_->speak(answer, cd);
   //       data += cd;}
   //       break;
   //    }
   //    if (answer.size() >= kk) {
   //       std::string cd;
   //       std::cout << answer << std::endl;
   //       festival_->speak(answer, cd);
   //       data += cd;
   //       answer.clear();
   //    }
      

   // }


//    answer = "Однажды на заре времени началась эра человечества. Тогда люди не могли представить, какие высоты достигнет наука, какие технологии будут доступны, как удобно станет жить в условиях современного мира. Тем не менее, они стремительно развивались, изобретали новые вещи, создавали искусство и культуру.\
// Сегодня мы живем в эпоху информационных технологий, которые изменили наш мир до неузнаваемости. Мы можем связаться со всеми уголками планеты за считанные секунды, получить доступ к мировой экономике и всей ее информации. Казалось бы, жизнь стала проще, эффективнее и удобнее.\
// Однако, возникают новые проблемы: информационная зависимость, нарушение личной жизни, манипуляции сознанием и дезинформация. Люди приобретаются электронными гаджетами, забывая оживительные эмоции, которые приносит природа и общение с другими людьми. Мы должны научиться использовать технологии в меру, чтобы они служили нам, а не мы их.\
// Более того, необходимо понимать, что технический прогресс не прекращается, и в будущем нас ждут еще более серьезные и глобальные проблемы. Решение этих проблем требует комплексного подхода и участия каждого из нас. Надо смотреть вперед, не ограничиваться своими текущими нуждами и желаниями.\
// В целом, жизнь не стоит на месте, и это радует. Но мы должны понимать, какая ответственность ложится на нас, чтобы мы могли жить в мире и гармонии со своим окружением. Техника – это инструмент, который помогает нам преодолевать трудности, и эпоха информационных технологий – это новое измерение нашей жизни. Но в первую очередь, мы обязаны помнить, что нам нужна забота, здоровье и общение в нашем ноу-хау мире.";
   int tts_num = std::stoi(pkg.param["tts"]);
   std::cout << "NUM " << tts_num << std::endl;
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
   std::cout << "отправлена озвучка" << std::endl;
   std::cout << "ASK END" << std::endl;
   std::cout << "==================" << std::endl;
   // std::ofstream out("dsfsdsf.wav");
   // out.write(data.c_str(), data.size());
   // out.close();
   // r->read(str);
   // std::cout << str.size() << std::endl;
   // std::string voice_question;
   // while (true) {
   //    r->read(str);
   //    if (str == "end") {
   //       break;
   //    }
   //    voice_question += str;
   // }
   // std::cout  << voice_question.size() << std::endl;
   // std::cout << voice_question.size() << std::endl;
   // std::cout << voice_question << std::endl;
   // // sphinx_->trans(voice_question, str);
   // std::string answer_text;
   // gpt_->ask("", voice_question, answer_text);
   // std::cout << answer_text << std::endl;
   // // w->write(answer_text + "\nend\n");
}
