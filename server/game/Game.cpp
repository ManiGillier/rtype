#include "Game.hpp"
#include "../../shared/components/Dependence.hpp"
#include "../../shared/components/Health.hpp"
#include "../../shared/components/HitBox.hpp"
#include "../../shared/components/Laser.hpp"
#include "../../shared/components/Position.hpp"
#include "../components/Acceleration.hpp"
#include "../components/Damager.hpp"
#include "../components/OutsideBoundaries.hpp"
#include "../components/Resistance.hpp"
#include "../components/Velocity.hpp"
#include "../systems/GameSystems.hpp"
#include "network/logger/Logger.hpp"
#include "network/server/Server.hpp"
#include <chrono>
#include <iostream>
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
            std::shared_ptr<Packet> newPlayerPacket =
                create_packet(NewPlayerPacket, p_id, l_id);
            this->sendPackets(newPlayerPacket);
        }
        _isRunning = true;
    }
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

std::pair<Entity, Entity> Game::addPlayer()
{
    Entity pl = _factory.createPlayer();
    Entity laser = _factory.createPlayerLaser(static_cast<int>(pl.getId()));

    _players.emplace(pl.getId(), laser.getId());
    return {pl, laser};
}

EntityFactory &Game::getFactory()
{
    return this->_factory;
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
}

void Game::initializeSystems()
{
    _registry
        .add_update_system<Position, Velocity, Acceleration, OutsideBoundaries>(
            Systems::movement_system, std::ref(*this));
    _registry.add_update_system<Position, Laser>(Systems::update_laser_system,
                                                 std::ref(*this));
    _registry.add_update_system<Health>(Systems::cleanup_system,
                                        std::ref(*this));
}

void Game::sendPackets(std::shared_ptr<Packet> packet)
{
    std::vector<std::shared_ptr<IPollable>> &pollables =
        _server.getPollManager().getPool();
    for (auto &pollable : pollables) {
        pollable->sendPacket(packet);
    }
}
