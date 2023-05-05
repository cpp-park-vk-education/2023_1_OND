#include "head.hpp"
#include <memory>
#include <iostream>

TEST(UserRegistrationTest, RegistrationNewUser) {
    StubReadSPtr stub = std::make_shared<StubRead>(
        rows{"username=user1\nmail=a@example.com\npassword=qwerty\ntoken=1234"});
    MockWriteSPtr mock = std::make_shared<MockWrite>();
    MockDatabaseSPtr db = std::make_shared<MockDatabase>();
    std::shared_ptr<Handler> reg = std::make_shared<UserRegistration>(db);
    reg->serve(mock, stub);
    EXPECT_EQ(mock->getData(), rows{"ok"});
    EXPECT_CALL(*db, insertUser("user1", "a@example.com", "password=qwerty", "1234"));
}

TEST(UserRegistrationTest, RegistrationWithExistUsername) {
    StubReadSPtr stub = std::make_shared<StubRead>(
        rows{"username=user1\nmail=a@example.com\npassword=qwerty\ntoken=1234",
             "username=user1\nmaiil=new@example.com\npassword=qwerty\ntoken=1234"});
    MockWriteSPtr mock = std::make_shared<MockWrite>();
    MockDatabaseSPtr db = std::make_shared<MockDatabase>();
    std::shared_ptr<Handler> reg = std::make_shared<UserRegistration>(db);
    reg->serve(mock, stub);
    rows res = rows{"ok", "error"};
    EXPECT_EQ(mock->getData(), res);
}

TEST(UserRegistrationTest, RegistrationWithExistMail) {
    StubReadSPtr stub = std::make_shared<StubRead>(
        rows{"username=user1\nmail=a@example.com\npassword=qwerty\ntoken=1234",
             "username=user2\nmaiil=b@example.com\npassword=qwerty\ntoken=1234"});
    MockWriteSPtr mock = std::make_shared<MockWrite>();
    MockDatabaseSPtr db = std::make_shared<MockDatabase>();
    std::shared_ptr<Handler> reg = std::make_shared<UserRegistration>(db);
    reg->serve(mock, stub);
    rows res = rows{"ok", "error"};
    EXPECT_EQ(mock->getData(), res);
}

TEST(GetUserDataTest, GetDataExistUser) {
    StubReadSPtr stub = std::make_shared<StubRead>(
        rows{"username=admin"});
    MockWriteSPtr mock = std::make_shared<MockWrite>();
    MockDatabaseSPtr db = std::make_shared<MockDatabase>();
    std::shared_ptr<Handler> reg = std::make_shared<GetUserData>(db);
    reg->serve(mock, stub);
    rows res = rows{"ok"};
    EXPECT_EQ(mock->getData(), res);
    rows data;
    EXPECT_CALL(*db, selectUser("admin", data));
}

TEST(GetUserDataTest, GetDataNotExistUser) {
    StubReadSPtr stub = std::make_shared<StubRead>(
        rows{"username=1213"});
    MockWriteSPtr mock = std::make_shared<MockWrite>();
    MockDatabaseSPtr db = std::make_shared<MockDatabase>();
    std::shared_ptr<Handler> reg = std::make_shared<GetUserData>(db);
    reg->serve(mock, stub);
    rows res = rows{"error"};
    EXPECT_EQ(mock->getData(), res);
    rows data;
    EXPECT_CALL(*db, selectUser("admin", data));
}
