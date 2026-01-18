#include "Lobby.hpp"
#include "network/logger/Logger.hpp"
#include "network/packets/impl/StartGamePacket.hpp"
#include <network/packets/impl/NewPlayerPacket.hpp>
#include <mutex>
#include <vector>

Lobby::Lobby()
    : _isPublic(false), _inGame(false), _game(_players, _playersMutex)
{
}

bool Lobby::addPlayer(std::shared_ptr<Player> &player)
{
    {
        std::lock_guard<std::mutex> lock(_playersMutex);
        if (this->_players.size() < MAX_PLAYER) {
            this->_players.push_back(player);
            return true;
        }
    }
    return false;
}

void Lobby::sendNewUsrnames()
{
    std::lock_guard<std::mutex> lock(_playersMutex);
    std::vector<std::string> names;

    for (auto &p : _players)
        names.push_back(p->getUsername());

    auto names_p = create_packet(NewPlayerPacket,names);

    for (auto &p : _players)
        p->sendPacket(names_p);
}

void Lobby::removePlayer(std::shared_ptr<Player> &player)
{
    {
        std::lock_guard<std::mutex> lock(_playersMutex);
        for (auto it = this->_players.begin(); it != this->_players.end();
             ++it) {
            if (it->get() == player.get()) {
                this->_players.erase(it);

                if (player->getEntityId().has_value()) {
                    auto [regMtx, reg] = _game.getRegistry();
                    std::lock_guard<std::mutex> lock(regMtx);
                    reg.kill_entity(
                        reg.entity_from_index(player->getEntityId().value().first));
                    reg.kill_entity(
                        reg.entity_from_index(player->getEntityId().value().second));
                    player->setEntityId(std::nullopt);
                }
                break;
            }
        }
    }
    this->sendNewUsrnames();
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

void Lobby::startGame(GameStartConfig config, int ticks)
{
    this->_game.loop(config, ticks);
    LOG("game end");
    this->_inGame = false;
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
