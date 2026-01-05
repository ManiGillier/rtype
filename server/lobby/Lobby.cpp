#include "Lobby.hpp"

bool Lobby::addPlayer(std::shared_ptr<Player> &player)
{
    if (this->_players.size() < MAX_PLAYER) {
        this->_players.push_back(player);
        this->_game.addPlayer(player);
        return true;
    }
    return false;
}

void Lobby::removePlayer(std::shared_ptr<Player> &player)
{
    for (auto it = this->_players.begin(); it != this->_players.end(); ++it) {
        if (it->get() == player.get()) {
            this->_players.erase(it);
            break;
        }
    }
    this->_game.removePlayer(player);
}

std::size_t Lobby::size() const
{
    return this->_players.size();
}

std::vector<std::shared_ptr<Player>> &Lobby::getPlayers()
{
    return this->_players;
}

bool Lobby::isInGame()
{
    std::lock_guard<std::mutex> lock(_inGameMutex);
    return this->_inGame;
}

void Lobby::setIsInGame(bool iig)
{
    std::lock_guard<std::mutex> lock(_inGameMutex);
    this->_inGame = iig;
}

void Lobby::startGame(int ticks)
{
    this->_game.loop(ticks);
    {
        std::lock_guard<std::mutex> lock(_inGameMutex);
        this->_inGame = false;
    }
}
