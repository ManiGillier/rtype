#include "RTypeServer.hpp"
#include "network/server/Server.hpp"
#include "player/Player.hpp"

RTypeServer::RTypeServer(int port, int ticks)
    : Server(port), _next_id(1), _ticks(ticks)
{
}

std::shared_ptr<IPollable> RTypeServer::createClient(int fd)
{
    auto p = std::make_shared<Player>(fd, this->getPollManager(), _next_id);
    _game.addPlayer(p);
    LOG("Player added to game");
    return p;
}

void RTypeServer::onClientConnect(std::shared_ptr<IPollable> client)
{
    LOG("Player connected fd=" << client->getFileDescriptor());
}

void RTypeServer::onClientDisconnect(std::shared_ptr<IPollable> client)
{
    LOG("Player disconnected fd=" << client->getFileDescriptor());
}

Game &RTypeServer::getGame()
{
    return _game;
}

int RTypeServer::getTicks() const
{
    return _ticks;
}
