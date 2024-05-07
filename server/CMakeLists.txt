set(SERVER_NAME udp_server)

include_directories(include src)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(SERVER_SRC
        src/WorkerManager.cpp
        src/UDPServer.cpp
        src/main.cpp
)

add_executable(${SERVER_NAME} ${SERVER_SRC})
target_link_libraries(${SERVER_NAME} PRIVATE uring)

