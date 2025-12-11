#include "R-TypeServer.hpp"
#include "network/logger/Logger.hpp"
#include <iostream>
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

    int launch()
    {
        if (_displayUsage)
            return displayUsage();

        // TODO: create an other thread for this.
        RtypeServer server(this->_port);
        server.up();

        auto server_loop = [](RtypeServer *server) {
            while (1)
                server->loop();
        };

        std::thread s(server_loop, &server);
        s.join();
        return 0;
    }

  private:
    int _ticks = 60;
    int _port = -1;
    bool _displayUsage = false;
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
