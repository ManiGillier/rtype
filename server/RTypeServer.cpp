#include "RTypeServer.hpp"
#include "network/server/Server.hpp"
#include "network/packets/impl/PlayerIdPacket.hpp"
#include "network/packets/impl/NewPlayerPacket.hpp"
#include "player/Player.hpp"
#include <memory>

RTypeServer::RTypeServer(int port, int ticks)
    : Server(port), _next_id(0), _ticks(ticks), _canStartGame(false)
{
}

std::shared_ptr<IPollable> RTypeServer::createClient(int fd)
{
    return std::make_shared<Player>(fd, this->getPollManager(), _next_id++);
}

void RTypeServer::onClientConnect(std::shared_ptr<IPollable> client)
{
    LOG("Player connected fd=" << client->getFileDescriptor());

    auto player = std::static_pointer_cast<Player>(client);
    // add player to get his entity id
    auto [e_player, e_laser] = _game.addPlayer();

    LOG("Player added to game with id=" << e_player.getId() << " and laser_id=" << e_laser.getId());

    // send back is entity id
    std::shared_ptr<ServerClient> sc =
        std::static_pointer_cast<ServerClient>(client);
    std::shared_ptr<Packet> p =
        create_packet(PlayerIdPacket, e_player.getId());
    sc->sendPacket(p);

    // create player 
    std::shared_ptr<Packet> newPlayerPacket =
        create_packet(NewPlayerPacket, e_player.getId(), e_laser.getId());

    for (std::shared_ptr<IPollable> &c : this->getPollManager().getPool()) {
        std::shared_ptr<ServerClient> clientToNotify =
            std::static_pointer_cast<ServerClient>(c);
        clientToNotify->sendPacket(newPlayerPacket);
    }
}

void RTypeServer::onClientDisconnect(std::shared_ptr<IPollable> client)
{
    auto player = std::static_pointer_cast<Player>(client);
    LOG("Player id=" << player->getId());
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

void RTypeServer::setStart()
{
    _canStartGame = true;
}

bool RTypeServer::canStart() const
{
    return _canStartGame;
}
