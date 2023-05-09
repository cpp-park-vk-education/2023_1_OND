add_executable(api_test src/sphinxtest.cpp)
add_executable(api_test src/festivaltest.cpp)
target_link_libraries(api_test api
                               GTest::gtest_main)
add_test(api_test api_test)