#include "./game/GameExecutor.hpp"
#include "./game/ClientInputsExecutor.hpp"
#include "RTypeServer.hpp"
#include "network/logger/Logger.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <thread>

class ArgsError : public std::exception
{
  public:
    ArgsError(const std::string &message) : message_(message) {}
    const char *what() const throw()
    {
        return message_.c_str();
    }

  private:
    std::string message_;
};

class RType
{
  public:
    RType(int argc, char **argv)
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
                    throw ArgsError("unexpected argument " +
                                    std::string(argv[i]));
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

    int displayUsage()
    {
        std::cout << "USAGE:" << std::endl;
        std::cout << "\t ./r-type_server {-p port} [-t tick (between 1 and "
                     "120) ] [-d]"
                  << std::endl;
        std::cout << "\t : {} = mendatory" << std::endl;
        std::cout << "\t : [] = optional" << std::endl;
        return 0;
    }

    void networkLoop()
    {
        RTypeServer server(this->_port, this->_ticks);
        server.up();
        server.getPacketListener().addExecutor(
            std::make_unique<GameExecutor>(server));
        server.getPacketListener().addExecutor(
            std::make_unique<ClientInputsExecutor>(server));

        while (1) {
            server.loop();
            if (_hasStarted) {
                server.getGame().sendAllPackets(server);
            }
            if (server.canStart() && !_hasStarted) {
                this->addThread(
                    std::thread(&Game::loop, std::ref(server.getGame()), this->_ticks));
                _hasStarted = !_hasStarted;
            }
        }
    }

    int launch()
    {
        if (_displayUsage)
            return displayUsage();

        this->addThread(std::thread(&RType::networkLoop, this));
        for (std::thread &th : this->_threads)
            th.join();
        return 0;
    }

    void addThread(std::thread &&t)
    {
        this->_threads.push_back(std::move(t));
    }

  private:
    int _ticks = 60;
    int _port = -1;
    bool _displayUsage = false;
    bool _hasStarted = false;
    std::vector<std::thread> _threads;
};

int main(int argc, char **argv)
{
    try {
        return RType(argc, argv).launch();
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        return 84;
    }
}
