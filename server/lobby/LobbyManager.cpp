#include "server/lobby/LobbyManager.hpp"
#include "server/lobby/Lobby.hpp"
#include <memory>
#include <network/logger/Logger.hpp>
#include <random>
#include <string>

LobbyManager::LobbyManager(int ticks) : _ticks(ticks) {}

void LobbyManager::newLobby(std::shared_ptr<Player> &player, bool publicl)
{
    std::string lobbyId = this->getRandomLobbyId(6);
    auto lobby = std::make_shared<Lobby>();

    player->setLobby(lobbyId);
    lobby->addPlayer(player);

    if (publicl)
        lobby->setPublic(true);

    {
        std::lock_guard<std::mutex> lock(_lobbiesMutex);
        this->_lobbies.emplace(lobbyId, lobby);
    }

    LOG("Player id " << player->getId() << " added to lobby " << lobbyId);
}

void LobbyManager::removePlayer(std::shared_ptr<Player> &player)
{
    auto playerLobbyId = player->getLobbyId();

    std::lock_guard<std::mutex> lock(_lobbiesMutex);
    auto it = _lobbies.find(playerLobbyId);
    if (it == _lobbies.end()) {
        return;
    }

    it->second->removePlayer(player);
    LOG("Player id " << player->getId() << " has quit lobby " << playerLobbyId);

    if (it->second->size() <= 0)
        this->_lobbies.erase(it);
}

bool LobbyManager::joinLobby(const std::string &lobbyId,
                             std::shared_ptr<Player> &player)
{
    std::shared_ptr<Lobby> lobby;
    {
        std::lock_guard<std::mutex> lock(_lobbiesMutex);
        auto it = _lobbies.find(lobbyId);
        if (it == _lobbies.end()) {
            return false;
        }
        lobby = it->second;
        player->setLobby(it->first);
    }
    return lobby->addPlayer(player);
}

bool LobbyManager::joinPublicLobby(std::shared_ptr<Player> &player)
{
    std::string publiclobby;

    {
        std::lock_guard<std::mutex> lock(_lobbiesMutex);
        for (auto &it : _lobbies) {
            if (it.second->isPublic() && !it.second->isInGame() &&
                !it.second->isFull()) {
                publiclobby = it.first;
                break;
            }
        }
    }

    this->removePlayer(player);
    if (!publiclobby.empty()) {
        return this->joinLobby(publiclobby, player);
    } else {
        this->newLobby(player, true);
        return true;
    }
}

void LobbyManager::leaveLobby(std::shared_ptr<Player> &player)
{
    this->removePlayer(player);
    this->newLobby(player, false);
}

void LobbyManager::startGame(const std::string &lobbyId)
{
    std::shared_ptr<Lobby> lobby;
    {
        std::lock_guard<std::mutex> lock(_lobbiesMutex);
        auto it = _lobbies.find(lobbyId);
        if (it == _lobbies.end()) {
            LOG("Cannot start game, lobby " << lobbyId << " not found");
            return;
        }
        lobby = it->second;
    }
    lobby->startGame(this->_ticks);
}

std::shared_ptr<Lobby> LobbyManager::getLobby(const std::string &lobbyId)
{
    std::lock_guard<std::mutex> lock(_lobbiesMutex);
    auto it = _lobbies.find(lobbyId);

    return (it != _lobbies.end()) ? it->second : nullptr;
}

std::string LobbyManager::getRandomLobbyId(std::size_t len)
{
    static const std::string allowed_chars{
        "123456789BCDFGHJKLMNPQRSTVWXZbcdfghjklmnpqrstvwxz"};

    static thread_local std::default_random_engine randomEngine(
        std::random_device{}());
    static thread_local std::uniform_int_distribution<int> randomDistribution(
        0, static_cast<int>(allowed_chars.size()) - 1);

    std::string id(len ? len : 32, '\0');

    for (std::string::value_type &c : id) {
        c = allowed_chars[randomDistribution(randomEngine)];
    }

    return id;
}
