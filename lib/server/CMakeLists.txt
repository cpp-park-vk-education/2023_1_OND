add_library(server src/server-tcp.cpp
                   src/chat_gpt.cpp
                   src/handler.cpp
                   src/serve_mux.cpp
                   src/session.cpp)

target_include_directories(server PUBLIC include)
target_link_libraries(server PUBLIC client_http)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif()
