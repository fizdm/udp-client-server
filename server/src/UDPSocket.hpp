#ifndef UDPSOCKET_HPP
#define UDPSOCKET_HPP

#include <cstdint>
#include <netinet/in.h>
#include <csignal>

class UDPSocket
{
public:
    explicit UDPSocket(uint16_t port)
    {
        Acquire(port);
    }

    void Acquire(uint16_t port)
    {
        fd_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (fd_ < 0)
        {
            throw std::runtime_error("Unable to acquire socket");
        }

        sockaddr_in local{
            .sin_family = AF_INET,
            .sin_port = htons(port),
            .sin_addr = {htonl(INADDR_ANY)},
        };

        if (bind(fd_, (sockaddr*) &local, sizeof(local)) != 0) {
            close(fd_);
            fd_ = -1;
            throw std::runtime_error("Unable to bind socket");
        }
    }

    [[nodiscard]] int GetFd() const
    {
        return fd_;
    }

private:
    int fd_{-1};
};
#endif //UDPSOCKET_HPP
