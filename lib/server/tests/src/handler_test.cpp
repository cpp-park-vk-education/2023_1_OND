#include <iostream>
#include <memory>
#include "head.hpp"

TEST(UserRegistrationTest, RegistrationNewUser) {
    StubReadSPtr stub = std::make_shared<StubRead>(
      rows{"username=user1\nmail=a@example.com\npassword=qwerty\ntoken=1234"});
    MockWriteSPtr mock = std::make_shared<MockWrite>();
    MockDatabaseSPtr db = std::make_shared<MockDatabase>();
    HandlerSPtr reg = std::make_shared<UserRegistration>(db);
    EXPECT_CALL(*db, insertUser("user1", "a@example.com", "qwerty", "1234"));
    reg->serve(mock, stub);
    EXPECT_EQ(mock->getData(), rows{"ok"});
}

TEST(UserRegistrationTest, RegistrationWithExistUsername) {
    StubReadSPtr stub = std::make_shared<StubRead>(
      rows{"username=user1\nmail=a@example.com\npassword=qwerty\ntoken=1234",
      "username=user1\nmail=new@example.com\npassword=qwerty\ntoken=1234"});
    MockWriteSPtr mock = std::make_shared<MockWrite>();
    MockDatabaseSPtr db = std::make_shared<MockDatabase>();
    HandlerSPtr reg = std::make_shared<UserRegistration>(db);
    EXPECT_CALL(*db, insertUser("user1", "a@example.com", "qwerty", "1234"));
    reg->serve(mock, stub);
    EXPECT_CALL(*db, insertUser("user1", "new@example.com", "qwerty", "1234"));
    reg->serve(mock, stub);
    rows res = rows{"ok", "error"};
    EXPECT_EQ(mock->getData(), res);
}

TEST(UserRegistrationTest, RegistrationWithExistMail) {
    StubReadSPtr stub = std::make_shared<StubRead>(
        rows{"username=user1\nmail=a@example.com\npassword=qwerty\ntoken=1234",
             "username=user2\nmail=a@example.com\npassword=qwerty\ntoken=1234"});
    MockWriteSPtr mock = std::make_shared<MockWrite>();
    MockDatabaseSPtr db = std::make_shared<MockDatabase>();
    HandlerSPtr reg = std::make_shared<UserRegistration>(db);
    EXPECT_CALL(*db, insertUser("user1", "a@example.com", "qwerty", "1234"));
    reg->serve(mock, stub);
    EXPECT_CALL(*db, insertUser("user2", "a@example.com", "qwerty", "1234"));
    reg->serve(mock, stub);
    rows res = rows{"ok", "error"};
    EXPECT_EQ(mock->getData(), res);
}

TEST(GetUserDataTest, GetDataExistUser) {
    StubReadSPtr stub = std::make_shared<StubRead>(
        rows{"username=admin"});
    MockWriteSPtr mock = std::make_shared<MockWrite>();
    MockDatabaseSPtr db = std::make_shared<MockDatabase>();
    std::shared_ptr<Handler> h = std::make_shared<GetUserData>(db);
    EXPECT_CALL(*db, selectUser("admin", testing::_)).WillOnce(
        testing::SetArgReferee<1>(std::vector<std::string>
            {"admin", "admin-token", "admin@example.com"}));
    h->serve(mock, stub);
    EXPECT_EQ(mock->getData(),
        rows{"username=admin\ntoken=admin-token\nmail=admin@example.com"});
}

TEST(GetUserDataTest, GetDataNotExistUser) {
    StubReadSPtr stub = std::make_shared<StubRead>(
        rows{"username=1213"});
    MockWriteSPtr mock = std::make_shared<MockWrite>();
    MockDatabaseSPtr db = std::make_shared<MockDatabase>();
    std::shared_ptr<Handler> h = std::make_shared<GetUserData>(db);
    EXPECT_CALL(*db, selectUser("admin", testing::_));
    h->serve(mock, stub);
    rows res = rows{"error"};
    EXPECT_EQ(mock->getData(), res);
}

TEST(ChangeUserDataTest, ChangeData) {
    StubReadSPtr stub = std::make_shared<StubRead>(
        rows{"username=admin\nnew_username=user\nnew_password=ffff"});
    MockWriteSPtr mock = std::make_shared<MockWrite>();
    MockDatabaseSPtr db = std::make_shared<MockDatabase>();
    std::shared_ptr<Handler> h = std::make_shared<ChangeUserData>(db);
    EXPECT_CALL(*db, alterUser("admin", "user", "", "ffff", ""));
    h->serve(mock, stub);
}

TEST(RemoveUserTest, RemoveExistsUser) {
    StubReadSPtr stub = std::make_shared<StubRead>(
        rows{"username=admin"});
    MockWriteSPtr mock = std::make_shared<MockWrite>();
    MockDatabaseSPtr db = std::make_shared<MockDatabase>();
    std::shared_ptr<Handler> h = std::make_shared<RemoveUser>(db);
    EXPECT_CALL(*db, deleteUser("admin"));
    h->serve(mock, stub);
    EXPECT_EQ(mock->getData(), rows{"ok"});
}

TEST(RemoveUserTest, RemoveNotExistsUser) {
    StubReadSPtr stub = std::make_shared<StubRead>(
        rows{"username=admin", "username=admin"});
    MockWriteSPtr mock = std::make_shared<MockWrite>();
    MockDatabaseSPtr db = std::make_shared<MockDatabase>();
    std::shared_ptr<Handler> h = std::make_shared<RemoveUser>(db);
    EXPECT_CALL(*db, deleteUser("admin"));
    h->serve(mock, stub);
    EXPECT_CALL(*db, deleteUser("admin"));
    h->serve(mock, stub);
    rows res{"ok", "error"};
    EXPECT_EQ(mock->getData(), res);
}

TEST(GetHistoryTest, LastQuestion) {
    StubReadSPtr stub = std::make_shared<StubRead>(
        rows{"username=admin"});
    MockWriteSPtr mock = std::make_shared<MockWrite>();
    MockDatabaseSPtr db = std::make_shared<MockDatabase>();
    std::shared_ptr<Handler> h = std::make_shared<GetHistory>(db);
    EXPECT_CALL(*db, getLastQuestion("admin", testing::_)).WillOnce(
        testing::SetArgReferee<1>("last question"));
    h->serve(mock, stub);
    EXPECT_EQ(mock->getData(), rows{"question=last question"});
}

TEST(GetHistoryTest, AnswersForQuestionByID) {
    StubReadSPtr stub = std::make_shared<StubRead>(
        rows{"question=1313"});
    MockWriteSPtr mock = std::make_shared<MockWrite>();
    MockDatabaseSPtr db = std::make_shared<MockDatabase>();
    std::shared_ptr<Handler> h = std::make_shared<GetHistory>(db);
    EXPECT_CALL(*db, selectQuestionAnswers("1313", testing::_))
        .WillOnce(testing::SetArgReferee<1>(std::vector<std::string>
            {"answer1", "answer2", "answer3"}));
    h->serve(mock, stub);
    rows res{"count_answers=3", "answer1", "answer2", "answer3"};
    EXPECT_EQ(mock->getData(), res);
}

TEST(RemoveHistoryTest, RemoveExistsUser) {
    StubReadSPtr stub = std::make_shared<StubRead>(
        rows{"username=human"});
    MockWriteSPtr mock = std::make_shared<MockWrite>();
    MockDatabaseSPtr db = std::make_shared<MockDatabase>();
    std::shared_ptr<Handler> h = std::make_shared<RemoveHistory>(db);
    EXPECT_CALL(*db, deleteUser("human"));
    h->serve(mock, stub);
    EXPECT_EQ(mock->getData(), rows{"ok"});
}

TEST(RemoveHistoryTest, RemoveNotExistsUser) {
    StubReadSPtr stub = std::make_shared<StubRead>(
        rows{"username=human", "username=human"});
    MockWriteSPtr mock = std::make_shared<MockWrite>();
    MockDatabaseSPtr db = std::make_shared<MockDatabase>();
    std::shared_ptr<Handler> h = std::make_shared<RemoveHistory>(db);
    EXPECT_CALL(*db, deleteUser("human"));
    h->serve(mock, stub);
    EXPECT_CALL(*db, deleteUser("human"));
    h->serve(mock, stub);
    rows res{"ok", "error"};
    EXPECT_EQ(mock->getData(), res);
}

TEST(RemoveHistoryTest, RemoveSelectQuestions) {
    StubReadSPtr stub = std::make_shared<StubRead>(
        rows{"question=13121"});
    MockWriteSPtr mock = std::make_shared<MockWrite>();
    MockDatabaseSPtr db = std::make_shared<MockDatabase>();
    std::shared_ptr<Handler> h = std::make_shared<RemoveHistory>(db);
    EXPECT_CALL(*db, deleteSelectQuestions("13121"));
    h->serve(mock, stub);
}

TEST(RemoveHistoryTest, RemoveUserHistory) {
    StubReadSPtr stub = std::make_shared<StubRead>(
        rows{"username=super\ndate=23.04.20"});
    MockWriteSPtr mock = std::make_shared<MockWrite>();
    MockDatabaseSPtr db = std::make_shared<MockDatabase>();
    std::shared_ptr<Handler> h = std::make_shared<RemoveHistory>(db);
    EXPECT_CALL(*db, deleteUserHistory("super", "23.04.20"));
    h->serve(mock, stub);
}

TEST(AskTest, NewQuestionFromTheUser) {
    StubReadSPtr stub = std::make_shared<StubRead>(
        rows{"username=super\nquestion=question asked by a voice"});
    MockWriteSPtr mock = std::make_shared<MockWrite>();
    MockDatabaseSPtr db = std::make_shared<MockDatabase>();
    MockChatGPTSPtr gpt = std::make_shared<MockChatGPT>();
    MockSphinxSPtr sphinx = std::make_shared<MockSphinx>();
    MockFestivalSPtr festival = std::make_shared<MockFestival>();
    std::shared_ptr<Handler> h = std::make_shared<Ask>(db, gpt, 
            sphinx, festival);
    
    EXPECT_CALL(*db, selectUser("super", testing::_)).WillOnce(
        testing::SetArgReferee<1>(std::vector<std::string>
        {"super", "token-super", "super@example.com"}));

    EXPECT_CALL(*sphinx, trans("question asked by a voice", testing::_))
        .WillOnce(testing::SetArgReferee<1>
            ("question is translated in text form"));

    EXPECT_CALL(*gpt, ask("token", "question is translated in text form",
                testing::_)).WillOnce(testing::SetArgReferee<2>
                    ("the answer is in the text"));

    EXPECT_CALL(*festival, speak("the answer is in the text", testing::_))
        .WillOnce(testing::SetArgReferee<1>("the answer is in the voice"));

    EXPECT_CALL(*db, insertQuestionAndAnswer("super",
            "question is translated in text form",
            "the answer is in the text"));

    h->serve(mock, stub);
    EXPECT_EQ(mock->getData(), rows{
        "text=the answer is in the text\nvoice=the answer is in the voice"});
}

TEST(AskTest, AgainQuestionFromTheUser) {
    StubReadSPtr stub = std::make_shared<StubRead>(
        rows{"username=spider"});
    MockWriteSPtr mock = std::make_shared<MockWrite>();
    MockDatabaseSPtr db = std::make_shared<MockDatabase>();
    MockChatGPTSPtr gpt = std::make_shared<MockChatGPT>();
    MockSphinxSPtr sphinx = std::make_shared<MockSphinx>();
    MockFestivalSPtr festival = std::make_shared<MockFestival>();
    std::shared_ptr<Handler> h = std::make_shared<Ask>(db, gpt, 
            sphinx, festival);

    EXPECT_CALL(*db, getLastQuestion("spider", testing::_))
        .WillOnce(testing::SetArgReferee<1>
            ("last question is translated in text form"));

    EXPECT_CALL(*gpt, ask("token", "last question is translated in text form",
                testing::_)).WillOnce(testing::SetArgReferee<2>
                    ("the answer is in the text"));

    EXPECT_CALL(*festival, speak("the answer is in the text", testing::_))
        .WillOnce(testing::SetArgReferee<1>("the answer is in the voice"));

    EXPECT_CALL(*db, insertAnswer("12", "the answer is in the text"));

    h->serve(mock, stub);
    EXPECT_EQ(mock->getData(), rows{
        "text=the answer is in the text\nvoice=the answer is in the voice"});
}

TEST(AskTest, NewQuestionFromGuest) {
    StubReadSPtr stub = std::make_shared<StubRead>(
        rows{"question=question asked by a voice"});
    MockWriteSPtr mock = std::make_shared<MockWrite>();
    MockDatabaseSPtr db = std::make_shared<MockDatabase>();
    MockChatGPTSPtr gpt = std::make_shared<MockChatGPT>();
    MockSphinxSPtr sphinx = std::make_shared<MockSphinx>();
    MockFestivalSPtr festival = std::make_shared<MockFestival>();
    std::shared_ptr<Handler> h = std::make_shared<Ask>(db, gpt, 
            sphinx, festival);
    EXPECT_CALL(*db, selectUser(testing::_, testing::_)).Times(0);

    EXPECT_CALL(*sphinx, trans("question asked by a voice", testing::_))
        .WillOnce(testing::SetArgReferee<1>
            ("question is translated in text form"));

    EXPECT_CALL(*gpt, ask("token", "question is translated in text form",
                testing::_)).WillOnce(testing::SetArgReferee<2>
                    ("the answer is in the text"));

    std::string voice_answer;
    EXPECT_CALL(*festival, speak("the answer is in the text", testing::_))
        .WillOnce(testing::SetArgReferee<1>("the answer is in the voice"));

    EXPECT_CALL(*db, insertQuestionAndAnswer(testing::_, testing::_,
        testing::_)).Times(0);

    h->serve(mock, stub);
    EXPECT_EQ(mock->getData(), rows{
        "text=the answer is in the text\nvoice=the answer is in the voice"});
}
