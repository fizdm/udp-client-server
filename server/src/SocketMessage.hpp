#ifndef SOCKETMESSAGE_HPP
#define SOCKETMESSAGE_HPP

#include <netinet/in.h>
#include <string>

struct SocketMessage
{
    int socket;
    sockaddr_in clientAddr;
    socklen_t clientLen;
    std::string msg;
};

#endif //SOCKETMESSAGE_HPP
