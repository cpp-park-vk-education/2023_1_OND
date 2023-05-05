cmake_minimum_required(VERSION 3.5)
project(yourvoice)

set(CMAKE_CXX_STANDARD 14)


enable_testing()
find_package(GTest REQUIRED)

include_directories(include)

set(SOURCE_FILES
    lib/server/src/server.cpp
    lib/server/src/api.cpp
)

add_executable(yourvoice ${SOURCE_FILES})


#add_subdirectory(tests)