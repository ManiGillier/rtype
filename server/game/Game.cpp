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
#include "systems/GameSystems.hpp"
#include <network/packets/impl/NewPlayerPacket.hpp>
#include "ticker/Ticker.hpp"
#include <chrono>
#include <optional>
#include <memory>
#include <mutex>
#include <thread>
#include <tuple>

Game::Game(std::mutex &playersMutex)
    : _playersMutex(playersMutex), _factory(this->_registry)
{
}

void Game::loop(int ticks)
{
    Ticker ticker(ticks);
    std::this_thread::sleep_for(std::chrono::milliseconds(200)); // TODO: remove this

    this->_isRunning = true;
    this->initializeComponents();
    this->initializeSystems();
    this->initPlayers();

    while (this->_isRunning) {
        ticker.now();

        this->_registryMutex.lock();
        _registry.update();
        this->_registryMutex.unlock();

        ticker.wait();
    }
    this->resetPlayersEntities();
}

void Game::addPlayer(std::shared_ptr<Player> &player)
{
    std::lock_guard<std::mutex> lock(_playersMutex);
    this->_players.push_back(player);
}

void Game::removePlayer(std::shared_ptr<Player> &player)
{
    std::lock_guard<std::mutex> lock(_playersMutex);
    for (auto it = this->_players.begin(); it != this->_players.end(); ++it) {
        if (it->get() == player.get()) {
            this->_players.erase(it);
            if (_isRunning || player->getEntityId().has_value()) {
                std::lock_guard<std::mutex> lock(_registryMutex);
                _registry.kill_entity(
                    _registry.entity_from_index(player->getEntityId().value()));
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
        for (auto &pl : _players) {
            {
                std::lock_guard<std::mutex> lockRegistry(_registryMutex);
                Entity player = _factory.createPlayer();
                Entity laser = _factory.createPlayerLaser(
                    static_cast<int>(player.getId()));
                pl->setEntityId(player.getId());
                playerData.push_back(
                    std::make_pair(player.getId(), laser.getId()));
            }
        }
    }
    for (const auto &[playerId, laserId] : playerData) {
        auto newPlayerPacket =
            create_packet(NewPlayerPacket, playerId, laserId);
        std::lock_guard<std::mutex> lock(_playersMutex);
        for (const auto &client : _players) {
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

void Game::initializeSystems()
{
    _registry
        .add_update_system<Position, Velocity, Acceleration, OutsideBoundaries>(
            Systems::position_system, std::ref(*this));
}

void Game::resetPlayersEntities()
{
    std::lock_guard<std::mutex> lock(_playersMutex);
    for (auto &it : _players)
        it->setEntityId(std::nullopt);
}

void Game::sendPackets(std::shared_ptr<Packet> packet)
{
    this->_playersMutex.lock();
    for (auto &client : _players) {
        client->sendPacket(packet);
    }
    this->_playersMutex.unlock();
}

std::tuple<std::mutex &, Registry &> Game::getRegistry()
{
    return std::tie(this->_registryMutex, this->_registry);
}
