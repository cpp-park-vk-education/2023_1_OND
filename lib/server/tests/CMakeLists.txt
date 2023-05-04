add_executable(server_test src/handler_test.cpp)
include_directories(include)

target_link_libraries(server_test server
                                 GTest::gtest_main
                                 GTest::gmock)

add_test(server_test server_test)