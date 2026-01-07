#include "Lobby.hpp"
#include <mutex>

Lobby::Lobby() : _isPublic(false), _inGame(false), _game(_playersMutex) {}

bool Lobby::addPlayer(std::shared_ptr<Player> &player)
{
    bool canAdd = false;
    {
        std::lock_guard<std::mutex> lock(_playersMutex);
        if (this->_players.size() < MAX_PLAYER) {
            this->_players.push_back(player);
            canAdd = true;
        }
    }

    if (canAdd) {
        this->_game.addPlayer(player);
        return true;
    }
    return false;
}

void Lobby::removePlayer(std::shared_ptr<Player> &player)
{
    {
        std::lock_guard<std::mutex> lock(_playersMutex);
        for (auto it = this->_players.begin(); it != this->_players.end();
             ++it) {
            if (it->get() == player.get()) {
                this->_players.erase(it);
                break;
            }
        }
    }
    this->_game.removePlayer(player);
}

std::mutex &Lobby::getPlayersMutex()
{
    return this->_playersMutex;
}

std::size_t Lobby::size() const
{
    std::lock_guard<std::mutex> lock(_playersMutex);
    return this->_players.size();
}

bool Lobby::isFull() const
{
    std::lock_guard<std::mutex> lock(_playersMutex);
    return this->_players.size() >= MAX_PLAYER;
}

std::vector<std::shared_ptr<Player>> &Lobby::getPlayers()
{
    return this->_players;
}

bool Lobby::isInGame()
{
    std::lock_guard<std::mutex> lock(_GameMutex);
    return this->_inGame;
}

void Lobby::setIsInGame(bool iig)
{
    std::lock_guard<std::mutex> lock(_GameMutex);
    this->_inGame = iig;
}

void Lobby::startGame(int ticks)
{
    this->_game.loop(ticks);
    {
        std::lock_guard<std::mutex> lock(_GameMutex);
        this->_inGame = false;
    }
}

Game &Lobby::getGame()
{
    return this->_game;
}

bool Lobby::isPublic() const
{
    std::lock_guard<std::mutex> lock(_publicMutex);
    return this->_isPublic;
}

void Lobby::setPublic(bool isPublic)
{
    std::lock_guard<std::mutex> lock(_publicMutex);
    this->_isPublic = isPublic;
}
