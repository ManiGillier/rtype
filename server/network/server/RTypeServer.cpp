#include "RTypeServer.hpp"
#include "../../player/Player.hpp"
#include <network/packets/impl/DestroyEntityPacket.hpp>
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

AccountDatabase & RTypeServer::getAccountDatabase()
{
    return this->db;
}

std::shared_ptr<IPollable> RTypeServer::createClient(int fd)
{
    // NOTE: id not used yet perhaps remove it later (was usefull during partI)
    return std::make_shared<Player>(fd, *this, _nextId++, std::nullopt);
}

void RTypeServer::onClientConnect(std::shared_ptr<IPollable> client)
{
    client->setDisabled(true);
    auto player = std::static_pointer_cast<Player>(client);

    LOG("Player connected to fd= " << client->getFileDescriptor());

    std::shared_ptr<ServerClient> sc =
        std::static_pointer_cast<ServerClient>(client);
}

void RTypeServer::onClientDisconnect(std::shared_ptr<IPollable> client)
{
    auto player = std::static_pointer_cast<Player>(client);
    LOG("Player disconnected to fd= " << client->getFileDescriptor());

    bool hasEntityId = player->getEntityId().has_value();
    auto lobbyId = player->getLobbyId();

    if (hasEntityId) {
        auto lobby = this->_lobbyManager.getLobby(lobbyId);
        if (lobby) {
            std::vector<uint16_t> toDestroy;
            toDestroy.push_back(static_cast<uint16_t>(player->getEntityId().value()));
            auto playerDisconnect = create_packet(DestroyEntityPacket, toDestroy);

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
    this->_lobbyManager.removePlayer(player);
}

bool RTypeServer::isConnected(const std::string &username)
{
    std::vector<std::shared_ptr<IPollable>> p = this->getPollManager().getPool();
    std::shared_ptr<Player> player = nullptr;

    for (std::shared_ptr<IPollable> pollable : p) {
        player = std::dynamic_pointer_cast<Player>(pollable);
        if (player == nullptr)
            continue;
        if (player->getUsername() == username)
            return true;
    }
    return false;
}
