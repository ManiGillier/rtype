#include "Game.hpp"
#include "components/Acceleration.hpp"
#include "components/Damager.hpp"
#include "components/OutsideBoundaries.hpp"
#include "components/Resistance.hpp"
#include "components/Velocity.hpp"
#include "network/logger/Logger.hpp"
#include "shared/components/Dependence.hpp"
#include "shared/components/Health.hpp"
#include "shared/components/HitBox.hpp"
#include "shared/components/Laser.hpp"
#include "shared/components/Position.hpp"
#include <chrono>
#include <memory>
#include <mutex>
#include <network/packets/impl/NewPlayerPacket.hpp>
#include <thread>

Game::Game() : _factory(this->_registry) {}

void Game::loop(int ticks)
{
    (void)ticks;
    this->_isRunning = true;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    this->initializeComponents();
    this->initPlayers();
}

void Game::addPlayer(std::shared_ptr<Player> &player)
{
    std::lock_guard<std::mutex> lock(_playersMutex);
    this->_players.push_back(std::make_pair(player, 0));
}

void Game::removePlayer(std::shared_ptr<Player> &player)
{
    std::lock_guard<std::mutex> lock(_playersMutex);
    for (auto it = this->_players.begin(); it != this->_players.end(); ++it) {
        if (it->first.get() == player.get()) {
            std::size_t entityId = it->second;
            this->_players.erase(it);

            if (_isRunning) {
                std::lock_guard<std::mutex> lock(_registryMutex);
                _registry.kill_entity(_registry.entity_from_index(entityId));
            }
            break;
        }
    }
}

void Game::initPlayers()
{
    std::vector<std::pair<std::size_t, std::size_t>> playerData;
    {
        std::lock_guard<std::mutex> lockPlayers(_playersMutex);
        for (auto &[client, playerId] : _players) {
            {
                std::lock_guard<std::mutex> lockRegistry(_registryMutex);
                Entity player = _factory.createPlayer();
                Entity laser = _factory.createPlayerLaser(
                    static_cast<int>(player.getId()));
                playerId = player.getId();
                playerData.push_back(
                    std::make_pair(player.getId(), laser.getId()));
            }
        }
    }
    for (const auto &[playerId, laserId] : playerData) {
        auto newPlayerPacket =
            create_packet(NewPlayerPacket, playerId, laserId);
        std::lock_guard<std::mutex> lock(_playersMutex);
        for (const auto &[client, _] : _players) {
            client->sendPacket(newPlayerPacket);
        }
    }
}

void Game::initializeComponents()
{
    _registry.register_component<Acceleration>();
    _registry.register_component<Damager>();
    _registry.register_component<Resistance>();
    _registry.register_component<Velocity>();
    _registry.register_component<Dependence>();
    _registry.register_component<OutsideBoundaries>();
    _registry.register_component<Health>();
    _registry.register_component<HitBox>();
    _registry.register_component<Laser>();
    _registry.register_component<Position>();
}
