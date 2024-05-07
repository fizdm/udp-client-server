set(SERVER_NAME udp_client)

set(SERVER_SRC
        src/main.cpp
)

add_executable(${SERVER_NAME} ${SERVER_SRC})

