#include "RTypeServer.hpp"

RTypeServer::RTypeServer(int port, int ticks) : Server(port), _ticks(ticks) {}

void RTypeServer::setTicks(int ticks)
{
    this->_ticks = ticks;
}

int RTypeServer::getTicks() const
{
    return this->_ticks;
}

// std::shared_ptr<IPollable> RTypeServer::createClient(int fd)
// {
// }
//
// void RTypeServer::onClientConnect(std::shared_ptr<IPollable> client)
// {
// }
//
// void RTypeServer::onClientDisconnect(std::shared_ptr<IPollable> client)
// {
// }
//
