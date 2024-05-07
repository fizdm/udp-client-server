#include <arpa/inet.h>
#include "UDPSocket.hpp"
#include <iostream>
#include <string>

int main() {
    UDPSocket sock;
    sockaddr_in local{
        .sin_family = AF_INET,
        .sin_port = htons(2024),
    };
    socklen_t localLen = sizeof(local);

    inet_aton("127.0.0.1", &local.sin_addr);

    while (true) {
        std::string resourceName;
        std::cout << "Enter message: " << std::endl;
        std::cin >> resourceName;

        sendto(sock.GetFd(), resourceName.data(), resourceName.size(), 0, reinterpret_cast<sockaddr*>(&local), localLen);

        char buf[1024];
        ssize_t recvLen{0};
        if (recvLen = recvfrom(sock.GetFd(), buf, sizeof(buf), 0, reinterpret_cast<sockaddr*>(&local), &localLen); recvLen <= 0) {
            std::cerr << "ERROR: No message received from server" << std::endl;
        }

        std::string msg(buf, recvLen);

        if (msg.starts_with("ERROR:"))
        {
            std::cerr << msg << std::endl;
        }
        else
        {
            std::cout << msg << std::endl;
        }
    }

    return 0;
}