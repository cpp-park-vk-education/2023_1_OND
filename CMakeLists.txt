cmake_minimum_required(VERSION 3.16)
project(YourVoice)

set(CMAKE_CXX_STANDARD 17)

option(BUILD_TESTS "build tests")
if(BUILD_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
endif()

add_subdirectory(lib/server)
add_subdirectory(lib/client_http)


add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} server -pthread -Wall -Werror -Wpedantic -Wextra)
