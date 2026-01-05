/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** rtype class
*/

#ifndef RTYPE
    #define RTYPE

#include "./network/server/RTypeServer.hpp"

class RType
{
  public:
    RType(int argc, char **argv);
    ~RType() = default;
    int displayUsage();
    int launch();
    void networkLoop();
    void initExecutor(RTypeServer &server);

  private:
    int _ticks = 60;
    int _port = -1;
    bool _displayUsage = false;
    bool _hasStarted = false;
};

#endif
