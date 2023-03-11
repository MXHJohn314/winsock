cmake_minimum_required(VERSION 3.13)

project(wsock_http_client)

add_executable(wsock_http_client __build.cpp)

add_subdirectory(src)

set_target_properties(wsock_http_client PROPERTIES CXX_STANDARD 20)

target_include_directories(wsock_http_client PRIVATE include)

target_link_libraries(wsock_http_client PRIVATE ws2_32 pthread)