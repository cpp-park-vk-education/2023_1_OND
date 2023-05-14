include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG 0817715923c9705e68994eb52ef9df3f6845beba)
FetchContent_MakeAvailable(cpr)

add_library(client_http src/client_http.cpp)

target_include_directories(client_http PUBLIC include)
target_include_directories(client_http PRIVATE ../cpr/include)

target_link_libraries(client_http PRIVATE cpr::cpr)
