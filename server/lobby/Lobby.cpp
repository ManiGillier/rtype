#include "Lobby.hpp"

bool Lobby::addPlayer(std::shared_ptr<Player> &player)
{
    if (this->_players.size() < MAX_PLAYER) {
        this->_players.push_back(player);
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
}

std::size_t Lobby::size() const
{
    return this->_players.size();
}

bool Lobby::startGame()
{
    // check nb of player here and create thread for game
    return true;
}
