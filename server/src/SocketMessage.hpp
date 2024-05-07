#ifndef SOCKETMESSAGE_HPP
#define SOCKETMESSAGE_HPP

#include <netinet/in.h>
#include <string>

struct SocketMessage
{
    int socket;
    sockaddr_in clientAddr;
    socklen_t clientLen{sizeof(clientAddr)};
    std::string msg;
};

#endif //SOCKETMESSAGE_HPP
