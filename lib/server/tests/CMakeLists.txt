add_executable(server_test src/test.cpp)
include_directories(include)

target_link_libraries(server_test server
                                 GTest::gtest_main)

add_test(server_test server_test)