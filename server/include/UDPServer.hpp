#ifndef UDPSERVER_HPP
#define UDPSERVER_HPP

#include <cstdint>
#include "WorkerManager.hpp"
#include "UringController.hpp"
#include "ResourceManager.hpp"
#include "SocketMessage.hpp"
#include "UDPSocket.hpp"

class UDPServer
{
public:
    explicit UDPServer(uint16_t port);
    /**
     * Blocking method
     */
    void Start();
    void Stop();

private:
    WorkerManager workerManager_;
    std::unique_ptr<UDPSocket> socket_{nullptr};
    std::atomic<bool> isRunning_{false};

    void run();
    void setup(uint16_t port);
};

#endif //UDPSERVER_HPP
