#include "handler.hpp"

UserRegistration::UserRegistration(DatabaseSPtr db): db_(db) {}
void UserRegistration::serve(WriterSPtr w, ReaderSPtr r) {}



GetUserData::GetUserData(DatabaseSPtr db): db_(db) {}
void GetUserData::serve(WriterSPtr w, ReaderSPtr r) {}


ChangeUserData::ChangeUserData(DatabaseSPtr db): db_(db) {}
void ChangeUserData::serve(WriterSPtr w, ReaderSPtr r) {}


RemoveUser::RemoveUser(DatabaseSPtr db): db_(db) {}
void RemoveUser::serve(WriterSPtr w, ReaderSPtr r) {}


GetHistory::GetHistory(DatabaseSPtr db): db_(db) {}
void GetHistory::serve(WriterSPtr w, ReaderSPtr r) {}


RemoveHistory::RemoveHistory(DatabaseSPtr db): db_(db) {}
void RemoveHistory::serve(WriterSPtr w, ReaderSPtr r) {}
