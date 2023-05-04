#include "handler.hpp"


UserRegistration::UserRegistration(std::shared_ptr<Database> db): db_(db) {}
void UserRegistration::serve(std::shared_ptr <Writer> w, std::shared_ptr<Reader> r) {}



GetUserData::GetUserData(std::shared_ptr<Database> db): db_(db) {}
void GetUserData::serve(std::shared_ptr <Writer> w, std::shared_ptr<Reader> r) {}


ChangeUserData::ChangeUserData(std::shared_ptr<Database> db): db_(db) {}
void ChangeUserData::serve(std::shared_ptr <Writer> w, std::shared_ptr<Reader> r) {}


RemoveUser::RemoveUser(std::shared_ptr<Database> db): db_(db) {}
void RemoveUser::serve(std::shared_ptr <Writer> w, std::shared_ptr<Reader> r) {}


Ask::Ask(std::shared_ptr<Database> db, std::shared_ptr<APIChatGPT> gpt): db_(db), gpt_(gpt) {}
void Ask::serve(std::shared_ptr <Writer> w, std::shared_ptr<Reader> r) {}


GetHistory::GetHistory(std::shared_ptr<Database> db): db_(db) {}
void GetHistory::serve(std::shared_ptr <Writer> w, std::shared_ptr<Reader> r) {}


RemoveHistory::RemoveHistory(std::shared_ptr<Database> db): db_(db) {}
void RemoveHistory::serve(std::shared_ptr <Writer> w, std::shared_ptr<Reader> r) {}
