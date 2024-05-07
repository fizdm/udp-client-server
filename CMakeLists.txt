cmake_minimum_required(VERSION 3.22)
project(udp_client_server)

set(CMAKE_CXX_STANDARD 20)

include_directories(commons/include)
add_subdirectory(server)
add_subdirectory(client)
