#include "Game.hpp"
#include "../../shared/components/Dependence.hpp"
#include "../../shared/components/Health.hpp"
#include "../../shared/components/HitBox.hpp"
#include "../../shared/components/Laser.hpp"
#include "../../shared/components/Position.hpp"
#include "../RTypeServer.hpp"
#include "../components/Acceleration.hpp"
#include "../components/BossTag.hpp"
#include "../components/Damager.hpp"
#include "../components/OutsideBoundaries.hpp"
#include "../components/Resistance.hpp"
#include "../components/Velocity.hpp"
#include "../systems/GameSystems.hpp"
#include "network/logger/Logger.hpp"
#include "network/packets/impl/HitboxSizeUpdatePacket.hpp"
#include "network/server/Server.hpp"
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <utility>

Game::Game(class Server &server)
    : _registry(), _factory(_registry), _isRunning(false), _server(server),
      _gameBoss(*this)
{
    initializeComponents();
    initializeSystems();
}

void Game::start()
{
    if (!_isRunning) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        for (auto const &[p_id, l_id] : _players) {
            auto hitBox = _registry.get<HitBox>(p_id);
            std::shared_ptr<Packet> newPlayerPacket =
                create_packet(NewPlayerPacket, p_id, l_id);

            this->sendPackets(newPlayerPacket);

            if (hitBox.has_value()) {
                std::shared_ptr<Packet> HitBoxSize =
                    create_packet(HitboxSizeUpdatePacket, p_id, hitBox->width,
                                  hitBox->height);
                this->sendPackets(HitBoxSize);
            }
        }
        _isRunning = true;
    }
}

void Game::stop()
{
    _isRunning = false;
    auto &r = static_cast<RTypeServer &>(_server);
    r.setRunning(false);
    r.getPollManager().wakeUp();
}

void Game::loop(int ticks)
{
    this->start();
    if (!_isRunning)
        return;
    auto tickDuration = std::chrono::milliseconds(1000 / ticks);

    LOG("Game loop started with: " << ticks << " ticks per second");

    while (_isRunning) {
        auto startTime = std::chrono::steady_clock::now();
        {
            std::lock_guard<std::mutex> lock(_registryMutex);
            _registry.update();
            if (!_isRunning)
                break;
            _gameBoss.update();
        }
        auto endTime = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            endTime - startTime);
        auto sleepTime = tickDuration - elapsed;
        if (sleepTime.count() > 0) {
            std::this_thread::sleep_for(sleepTime);
        }
    }
}

std::pair<std::size_t, std::size_t> Game::addPlayer()
{
    if (_isRunning)
        return {0, 0};
    {
        std::lock_guard<std::mutex> lock(_registryMutex);
        Entity pl = _factory.createPlayer();
        Entity laser = _factory.createPlayerLaser(static_cast<int>(pl.getId()));

        _players.emplace(pl.getId(), laser.getId());
        return {pl.getId(), laser.getId()};
    }
}

void Game::RemovePlayer(std::size_t id)
{
    {
        std::lock_guard<std::mutex> lock(_registryMutex);
        if (_players.contains(id))
            _players.erase(id);
    }
}

EntityFactory &Game::getFactory()
{
    return this->_factory;
}

GameBoss &Game::getGameBoss()
{
    return this->_gameBoss;
}

Registry &Game::getRegistry()
{
    return _registry;
}

std::mutex &Game::getRegistryMutex()
{
    return _registryMutex;
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
    _registry.register_component<BossTag>();
}

void Game::initializeSystems()
{
    _registry
        .add_update_system<Position, Velocity, Acceleration, OutsideBoundaries>(
            Systems::movement_system, std::ref(*this));
    _registry.add_update_system<Position, Laser>(Systems::update_laser_system,
                                                 std::ref(*this));
    _registry.add_update_system<Position, HitBox>(Systems::collision_system,
                                                  std::ref(*this));
    _registry.add_update_system<Health>(Systems::cleanup_system,
                                        std::ref(*this));
}

std::unordered_map<std::size_t, std::size_t> &Game::getPlayers()
{
    return this->_players;
}

void Game::sendPackets(std::shared_ptr<Packet> packet)
{
    std::vector<std::shared_ptr<IPollable>> &pollables =
        _server.getPollManager().getPool();
    for (auto &pollable : pollables) {
        pollable->sendPacket(packet);
    }
}

bool Game::isRunning() const
{
    return _isRunning;
}
