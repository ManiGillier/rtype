#include "RTypeServer.hpp"
#include "network/packets/impl/DespawnPlayerPacket.hpp"
#include "network/packets/impl/NewPlayerPacket.hpp"
#include "network/packets/impl/PlayerIdPacket.hpp"
#include "network/server/Server.hpp"
#include "player/Player.hpp"
#include <memory>

RTypeServer::RTypeServer(int port, int ticks)
    : Server(port), _next_id(0), _ticks(ticks), _canStartGame(false),
      _game(*this)
{
}

std::shared_ptr<IPollable> RTypeServer::createClient(int fd)
{
    // add player to get his entity id
    auto [e_player, _] = _game.addPlayer();
    return std::make_shared<Player>(fd, *this,
                                    e_player.getId());
}

void RTypeServer::onClientConnect(std::shared_ptr<IPollable> client)
{
    LOG("Player connected fd=" << client->getFileDescriptor());

    auto player = std::static_pointer_cast<Player>(client);

    LOG("Player added to game with id=" << player->getId());
    // send back is entity id
    std::shared_ptr<ServerClient> sc =
        std::static_pointer_cast<ServerClient>(client);
    std::shared_ptr<Packet> p = create_packet(PlayerIdPacket, player->getId());
    sc->sendPacket(p);
}

void RTypeServer::onClientDisconnect(std::shared_ptr<IPollable> client)
{
    auto player = std::static_pointer_cast<Player>(client);
    LOG("Player id=" << player->getId());

    std::shared_ptr<Packet> playerDisconnect =
        create_packet(DespawnPlayerPacket, player->getId());

    for (std::shared_ptr<IPollable> &c : this->getPollManager().getPool()) {
        std::shared_ptr<ServerClient> clientToNotify =
            std::static_pointer_cast<ServerClient>(c);
        clientToNotify->sendPacket(playerDisconnect);
    }
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
