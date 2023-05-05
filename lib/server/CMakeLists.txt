add_executable(api_test src/sphinxtest.cpp)
target_link_libraries(api_test api
                               GTest::gtest_main)
add_test(api_test api_test)