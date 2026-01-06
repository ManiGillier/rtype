#include "RTypeServer.hpp"
#include "../../player/Player.hpp"
#include <memory>
#include <mutex>
#include <optional>

RTypeServer::RTypeServer(int port, int ticks)
    : Server(port), _ticks(ticks), _nextId(0), _lobbyManager(ticks)
{
}

void RTypeServer::setTicks(int ticks)
{
    this->_ticks = ticks;
}

int RTypeServer::getTicks() const
{
    return this->_ticks;
}

LobbyManager &RTypeServer::getLobbyManager()
{
    return this->_lobbyManager;
}

void RTypeServer::cleanFinishedGame()
{
    this->_threadPool.cleanup();
}

ThreadPool &RTypeServer::getGameThreadPool()
{
    return this->_threadPool;
}

std::shared_ptr<IPollable> RTypeServer::createClient(int fd)
{
    // NOTE: id not used yet perhaps remove it later (was usefull during partI)
    return std::make_shared<Player>(fd, *this, _nextId++, std::nullopt);
}

void RTypeServer::onClientConnect(std::shared_ptr<IPollable> client)
{
    auto player = std::static_pointer_cast<Player>(client);

    LOG("Player connected to fd= " << client->getFileDescriptor());

    this->_lobbyManager.newLobby(player);
    std::shared_ptr<ServerClient> sc =
        std::static_pointer_cast<ServerClient>(client);
    std::shared_ptr<Packet> p = create_packet(PlayerIdPacket, player->getId());
    sc->sendPacket(p);
}

void RTypeServer::onClientDisconnect(std::shared_ptr<IPollable> client)
{
    auto player = std::static_pointer_cast<Player>(client);

    LOG("Player disconnected to fd= " << client->getFileDescriptor());
    this->_lobbyManager.removePlayer(player);

    // send despawn packet if player has an entity id (which meens his in game)
    if (player->getEntityId().has_value()) {
        std::shared_ptr<Packet> playerDisconnect =
            create_packet(DespawnPlayerPacket, player->getId());
        auto &lobby = this->_lobbyManager.getLobbies()[player->getLobbyId()];
        auto &playersMutex = lobby->getPlayersMutex();
        {
            std::lock_guard<std::mutex> lock(playersMutex);
            auto &players = lobby->getPlayers();

            for (auto &it : players) {
                it->sendPacket(playerDisconnect);
            }
        }
    }
}
