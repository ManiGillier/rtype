#include "RType.hpp"
#include "./error/ArgsError.hpp"
#include "network/logger/Logger.hpp"
#include "server/network/executor/GameStartExecutor.hpp"
#include "server/network/server/RTypeServer.hpp"
#include <iostream>
#include <string>

RType::RType(int argc, char **argv)
{
    if (argc <= 1)
        throw ArgsError("missing arguments try: " + std::string(argv[0]) +
                        " --help");
    if (argc == 2) {
        if (std::string(argv[1]) == "--help") {
            this->displayUsage();
            return;
        }
        throw ArgsError("unexpected argument " + std::string(argv[1]));
    }
    for (int i = 1; i < argc; i++) {
        const std::string arg(argv[i]);
        if (i + 1 < argc || arg == "-d") {
            if (arg == "-t") {
                _ticks = std::atoi(argv[i + 1]);
            } else if (arg == "-p") {
                _port = std::atoi(argv[i + 1]);
            } else if (arg == "-d") {
                Logger::shouldLog = true;
            } else {
                throw ArgsError("unexpected argument " + std::string(argv[i]));
            }
            i += 1;
        } else {
            throw ArgsError("unexpected argument " + std::string(argv[i]) +
                            " wihtout value");
        }
    }
    if (_ticks < 1 || _ticks > 120)
        throw ArgsError("We’re not at the butcher’s shop; "
                        "please try a different tick value.");
}

int RType::displayUsage()
{
    std::cout << "USAGE:" << std::endl;
    std::cout << "\t ./r-type_server {-p port} [-t tick (between 1 and "
                 "120) ] [-d]"
              << std::endl;
    std::cout << "\t : {} = mendatory" << std::endl;
    std::cout << "\t : [] = optional" << std::endl;
    exit(0);
}

void RType::initExecutor(RTypeServer &server)
{
    server.getPacketListener().addExecutor(
        std::make_unique<GameStartExecutor>(server));
    // server.getPacketListener().addExecutor(
    //     std::make_unique<ClientInputsExecutor>(server));
    //
}

void RType::networkLoop()
{
    RTypeServer server(this->_port, this->_ticks);
    if (!server.up()) {
        LOG_ERR("RType server Can't connect");
        return;
    }

    this->initExecutor(server);

    while (server.isUp()) {
        server.loop();
        server.cleanFinishedGame();
    }
}

int RType::launch()
{
    if (_displayUsage)
        return displayUsage();

    std::thread server(&RType::networkLoop, this);
    server.join();
    return 0;
}
