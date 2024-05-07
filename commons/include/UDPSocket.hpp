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
        fd_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (fd_ < 0)
        {
            throw std::runtime_error("Unable to acquire socket");
        }
    }

    [[nodiscard]] int GetFd() const
    {
        return fd_;
    }

    void Close()
    {
        close(fd_);
        fd_ = -1;
    }

    ~UDPSocket()
    {
        Close();
    }

private:
    int fd_{-1};
};
#endif //UDPSOCKET_HPP
