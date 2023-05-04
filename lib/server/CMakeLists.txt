add_library(server src/server-tcp.cpp)

target_include_directories(server PUBLIC include)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif()
