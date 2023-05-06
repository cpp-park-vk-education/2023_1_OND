#include "head.hpp"
#include <memory>
#include <iostream>

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
    rows data;
    EXPECT_CALL(*db, selectUser("admin", data));
    h->serve(mock, stub);
}

TEST(GetUserDataTest, GetDataNotExistUser) {
    StubReadSPtr stub = std::make_shared<StubRead>(
        rows{"username=1213"});
    MockWriteSPtr mock = std::make_shared<MockWrite>();
    MockDatabaseSPtr db = std::make_shared<MockDatabase>();
    std::shared_ptr<Handler> h = std::make_shared<GetUserData>(db);
    rows data;
    EXPECT_CALL(*db, selectUser("admin", data));
    h->serve(mock, stub);
    rows res = rows{"error"};
    EXPECT_EQ(mock->getData(), res);
}

TEST(ChangeUserDataTest, ChangeData) {
    StubReadSPtr stub = std::make_shared<StubRead>(
        rows{"username=admin\nnew_username=user\nnew_password=ffff"});
    MockWriteSPtr mock = std::make_shared<MockWrite>();
    MockDatabaseSPtr db = std::make_shared<MockDatabase>();
    std::shared_ptr<Handler> h = std::make_shared<GetUserData>(db);
    EXPECT_CALL(*db, alterUser("admin", "user", "", "ffff", ""));
    h->serve(mock, stub);
}

TEST(RemoveUserTest, RemoveExistsUser) {
    StubReadSPtr stub = std::make_shared<StubRead>(
        rows{"username=admin"});
    MockWriteSPtr mock = std::make_shared<MockWrite>();
    MockDatabaseSPtr db = std::make_shared<MockDatabase>();
    std::shared_ptr<Handler> h = std::make_shared<GetUserData>(db);
    EXPECT_CALL(*db, deleteUser("admin"));
    h->serve(mock, stub);
    EXPECT_EQ(mock->getData(), rows{"ok"});
}

TEST(RemoveUserTest, RemoveNotExistsUser) {
    StubReadSPtr stub = std::make_shared<StubRead>(
        rows{"username=admin", "username=admin"});
    MockWriteSPtr mock = std::make_shared<MockWrite>();
    MockDatabaseSPtr db = std::make_shared<MockDatabase>();
    std::shared_ptr<Handler> h = std::make_shared<GetUserData>(db);
    EXPECT_CALL(*db, deleteUser("admin"));
    h->serve(mock, stub);
    EXPECT_CALL(*db, deleteUser("admin"));
    h->serve(mock, stub);
    rows res{"ok", "error"};
    EXPECT_EQ(mock->getData(), res);
}