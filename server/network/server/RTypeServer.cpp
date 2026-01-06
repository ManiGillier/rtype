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

    bool hasEntityId = player->getEntityId().has_value();
    auto lobbyId = player->getLobbyId();
    auto playerId = player->getId();

    if (hasEntityId) {
        auto &lobbies = this->_lobbyManager.getLobbies();
        auto lobbyIt = lobbies.find(lobbyId);

        if (lobbyIt != lobbies.end() && lobbyIt->second) {
            auto &lobby = lobbyIt->second;

            std::shared_ptr<Packet> playerDisconnect =
                create_packet(DespawnPlayerPacket, playerId);

            auto &playersMutex = lobby->getPlayersMutex();
            {
                std::lock_guard<std::mutex> lock(playersMutex);
                auto &players = lobby->getPlayers();
                for (auto &it : players) {
                    if (it && it != player) {
                        it->sendPacket(playerDisconnect);
                    }
                }
            }
        }
    }
    this->_lobbyManager.removePlayer(player);
}
