/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** rtype class
*/

#ifndef RTYPE
    #define RTYPE

#include <thread>
#include <vector>

class RType
{
  public:
    RType(int argc, char **argv);
    ~RType() = default;
    int displayUsage();
    void networkLoop();
    int launch();
    void addThread(std::thread &&t);

  private:
    int _ticks = 60;
    int _port = -1;
    bool _displayUsage = false;
    bool _hasStarted = false;
    std::vector<std::thread> _threads;
};

#endif
