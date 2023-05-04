cmake_minimum_required(VERSION 3.5)
project(myproject)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

set(SOURCE_FILES
    lib/server/src/server.cpp
    lib/server/src/api.cpp
)

add_executable(myproject ${SOURCE_FILES})

#enable_testing()
#find_package(GTest REQUIRED)

#add_subdirectory(tests)