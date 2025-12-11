#include "Game.hpp"
#include "../../shared/components/Dependence.hpp"
#include "../../shared/components/Health.hpp"
#include "../../shared/components/HitBox.hpp"
#include "../../shared/components/Laser.hpp"
#include "../../shared/components/Position.hpp"
#include "../components/Acceleration.hpp"
#include "../components/Damager.hpp"
#include "../components/Resistance.hpp"
#include "../components/Velocity.hpp"
#include "../systems/GameSystems.hpp"
#include "ecs/sparse_array/SparseArray.hpp"

Game::Game() : _registry(), _factory(_registry), _isRunning(false)
{
    initializeComponents();
    initializeSystems();
}

void Game::start()
{
    if (!_isRunning) {
        this->addBodss();
        _isRunning = true;
    }
}

void Game::update()
{
    if (!_isRunning)
        return;

    //...
    _registry.update();
}

Entity Game::addPlayer(std::shared_ptr<Player> &player)
{
    Entity pl = _factory.createPlayer();

    // can't use for now need network class
    _players.emplace(player->getId(), std::move(pl));
    _factory.createPlayerLaser(static_cast<int>(pl.getId()));
    return pl;
}

void Game::removePlayer(std::shared_ptr<Player> &player)
{
    _players.erase(player->getId());
}

Entity Game::addBodss()
{
    auto boss = _factory.createBoss();
    return boss;
}

Registry &Game::getRegistry()
{
    return _registry;
}

void Game::initializeComponents()
{
    _registry.register_component<Acceleration>();
    _registry.register_component<Damager>();
    _registry.register_component<Resistance>();
    _registry.register_component<Velocity>();
    _registry.register_component<Dependence>();
    _registry.register_component<Health>();
    _registry.register_component<HitBox>();
    _registry.register_component<Laser>();
    _registry.register_component<Position>();
}

void Game::initializeSystems()
{
    _registry.add_update_system<Position, Velocity, Acceleration>(
        Systems::movement_system, 0);
    _registry.add_update_system<Position, Dependence, Laser>(
        Systems::dependence_system, 0);
    _registry.add_update_system<Position, HitBox>(
        Systems::collision_system, 0);
    _registry.add_update_system<Health>(
        Systems::cleanup_system, 0);
}
