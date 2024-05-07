cmake_minimum_required(VERSION 3.28)
project(udp_client_server)

set(CMAKE_CXX_STANDARD 17)

include_directories(commons/include)
add_subdirectory(server)
