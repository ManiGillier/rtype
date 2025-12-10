#include "game/Game.hpp"
#include "player/Player.hpp"
#include <iostream>
#include <memory>
#include <string>

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
                    _ticks = std::atoi(arg.c_str());
                } else if (arg == "-p") {
                    _port = std::atoi(arg.c_str());
                } else if (arg == "-d") {
                    _debug = true;
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
    }

    int displayUsage()
    {
        std::cout << "USAGE:" << std::endl;
        std::cout << "\t ./r-type_server {-p port} [-t tick] [-d]" << std::endl;
        std::cout << "\t : {} = mendatory" << std::endl;
        std::cout << "\t : [] = optional" << std::endl;
        return 0;
    }

    int launch()
    {
        if (_displayUsage)
            return displayUsage();
        return 0;
    }

  private:
    bool _debug = false;
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
