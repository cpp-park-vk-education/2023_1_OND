add_library(server src/server-tcp.cpp)

target_include_directories(server PUBLIC include)
target_link_libraries(server PUBLIC client_http)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif()
