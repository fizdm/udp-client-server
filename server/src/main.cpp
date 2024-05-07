#include "UDPServer.hpp"

#include <csignal>

static std::function<void()> sigIntHandler;
void signalHandler([[maybe_unused]] int signal)
{
    sigIntHandler();
}

int main()
{
    UDPServer updServer(2024);

    sigIntHandler = [&](){
        updServer.Stop();
    };
    std::signal(SIGINT, signalHandler);
    updServer.Start();
}