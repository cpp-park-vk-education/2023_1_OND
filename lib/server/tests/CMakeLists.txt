add_executable(server_test src/handler_test.cpp
                           src/chat_gpt.cpp
                           src/serve_mux.cpp)
include_directories(include)

target_link_libraries(server_test server
                                 GTest::gtest_main
                                 GTest::gmock)

add_test(server_test server_test)