#include "handler.hpp"


UserRegistration::UserRegistration(DatabaseSPtr db): db_(db) {}
void UserRegistration::serve(WriterSPtr w, ReaderSPtr r) {}



GetUserData::GetUserData(DatabaseSPtr db): db_(db) {}
void GetUserData::serve(WriterSPtr w, ReaderSPtr r) {
    std::string str;
    while (true) {
      r->read(str);
      if (str == "end") {
         break;
      }
      std::cout << str << std::endl;
    }
}


ChangeUserData::ChangeUserData(DatabaseSPtr db): db_(db) {}
void ChangeUserData::serve(WriterSPtr w, ReaderSPtr r) {}


RemoveUser::RemoveUser(DatabaseSPtr db): db_(db) {}
void RemoveUser::serve(WriterSPtr w, ReaderSPtr r) {}


Ask::Ask(DatabaseSPtr db, std::shared_ptr<APIChatGPT> gpt,
         std::shared_ptr<APISphinx> sphinx,
         std::shared_ptr<APIFestival> festival):
            db_(db), gpt_(gpt), sphinx_(sphinx), festival_(festival) {}
void Ask::serve(WriterSPtr w, ReaderSPtr r) {}


GetHistory::GetHistory(DatabaseSPtr db): db_(db) {}
void GetHistory::serve(WriterSPtr w, ReaderSPtr r) {}


RemoveHistory::RemoveHistory(DatabaseSPtr db): db_(db) {}
void RemoveHistory::serve(WriterSPtr w, ReaderSPtr r) {}
