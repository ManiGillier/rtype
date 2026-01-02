#include "server/lobby/LobbyManager.hpp"
#include "server/lobby/Lobby.hpp"
#include <memory>
#include <network/logger/Logger.hpp>
#include <random>
#include <string>

void LobbyManager::newLobby(std::shared_ptr<Player> &player)
{
    std::string lobbyId = this->getRandomLobbyId(6);
    auto lobby = std::make_unique<Lobby>();

    player->setLobby(lobbyId);
    lobby->addPlayer(player);

    LOG("Player id " << player->getId() << " added to lobby " << lobbyId);
    this->_lobbies.emplace(lobbyId, std::move(lobby));
}

void LobbyManager::removePlayer(std::shared_ptr<Player> &player)
{
    auto playerLobbyId = player->getLobby();

    this->_lobbies[playerLobbyId]->removePlayer(player);
    LOG("Player id " << player->getId() << " has quit lobby " << playerLobbyId);

    if (this->_lobbies[playerLobbyId]->size() <= 0)
        this->_lobbies.erase(playerLobbyId);
}

bool LobbyManager::joinLobby(const std::string &lobbyId, std::shared_ptr<Player> &player)
{
    // TODO: do something if can no join desired lobby
    auto hasJoin = this->_lobbies[lobbyId]->addPlayer(player);

    return hasJoin;
}

void LobbyManager::leaveLobby(std::shared_ptr<Player> &player)
{
   this->removePlayer(player);
   this->newLobby(player);
}

bool LobbyManager::startGame(const std::string &lobbyId)
{
    return this->_lobbies[lobbyId]->startGame();
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
