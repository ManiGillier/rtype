#include "Server.hpp"
#include "player/Player.hpp"
#include "network/server/Server.hpp"

RtypeServer::RtypeServer(int port) : Server(port), _next_id(1) {}

std::shared_ptr<IPollable> RtypeServer::createClient(int fd)
{
    auto p = std::make_shared<Player>(fd, this->getPollManager(), _next_id);
    _game.addPlayer(p);
    LOG("Player added to game");
    return p;
}

void RtypeServer::onClientConnect(std::shared_ptr<IPollable> client)
{
    LOG("Player connected fd=" << client->getFileDescriptor());
}

void RtypeServer::onClientDisconnect(std::shared_ptr<IPollable> client)
{
    LOG("Player disconnected fd=" << client->getFileDescriptor());
}
