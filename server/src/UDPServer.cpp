#include "UDPServer.hpp"
#include "ResourceManager.hpp"
#include "UDPSocket.hpp"
#include "SocketMessage.hpp"
#include <iostream>
#include <arpa/inet.h>

UDPServer::UDPServer(uint16_t port) :
    socket_{std::make_unique<UDPSocket>(port)} {
    setup(port);
}

void UDPServer::Start() {
    isRunning_.store(true, std::memory_order_relaxed);
    run();
}

void UDPServer::Stop() {
    isRunning_.store(false, std::memory_order_relaxed);
}

void UDPServer::run() {
    std::cout << "UDP server started" << std::endl;

    while (isRunning_.load(std::memory_order_relaxed)) {
        SocketMessage socketMessage;
        socketMessage.socket = socket_->GetFd();
        char tempBuf[ResourceManager::MAX_RESOURCE_NAME_SIZE];

        // TODO: make non blocking
        ssize_t recvLen{0};
        if (recvLen = recvfrom(socket_->GetFd(), tempBuf, sizeof(tempBuf), 0,
                               reinterpret_cast<sockaddr*>(&socketMessage.clientAddr),
                               &socketMessage.clientLen);
            recvLen <= 0) {
            continue;
        }

        if (recvLen == 1 && tempBuf[0] == '\n') {
            continue;
        }

        socketMessage.msg = std::string(tempBuf, tempBuf[recvLen - 1] == '\n' ? recvLen - 1 : recvLen);

        std::cout << "New UDP message" << std::endl;

        workerManager_.Emplace([socketMessage]() {
            SocketMessage internalMessage = socketMessage;
            auto resourceContent = ResourceManager::GetResource(internalMessage.msg);
            if (!resourceContent) {
                internalMessage.msg = "ERROR: Unable to find resource\n";
            } else {
                internalMessage.msg = std::move(resourceContent.value());
            }

            printf("Received packet from %s:%d\n", inet_ntoa(internalMessage.clientAddr.sin_addr), ntohs(internalMessage.clientAddr.sin_port));
            ssize_t res = sendto(internalMessage.socket, internalMessage.msg.c_str(), internalMessage.msg.size(), 0,
                                 reinterpret_cast<sockaddr*>(&internalMessage.clientAddr),
                                 internalMessage.clientLen);
        });
    }
}

void UDPServer::setup(uint16_t port) {
    sockaddr_in local{
        .sin_family = AF_INET,
        .sin_port = htons(port),
        .sin_addr = {htonl(INADDR_ANY)},
    };

    if (bind(socket_->GetFd(), reinterpret_cast<sockaddr*>(&local), sizeof(local)) != 0) {
        socket_ = nullptr;
        throw std::runtime_error("Unable to bind socket");
    }
}
