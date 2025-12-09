#include "Game.hpp"
#include "../components/Collision.hpp"
#include "../components/EntityType.hpp"
#include "../components/Health.hpp"
#include "../components/Laser.hpp"
#include "../components/Motion.hpp"
#include "../components/Position.hpp"
#include "../systems/GameSystems.hpp"

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

Entity Game::addPlayer(const std::unique_ptr<Player>
                           &player /* Player *player (client abstraction) */)
{
    Entity pl = _factory.createPlayer();

    // can't use for now need network class
    _players.emplace(player->getId(), std::move(pl));
    _factory.createPlayerLaser(player->getId());
    return pl;
}

void Game::removePlayer(const std::unique_ptr<Player>
                            &player /* Player *player (client abstraction) */)
{
    _players.erase(player->getId());
}

Entity Game::addBodss()
{
    auto boss = _factory.createBoss();
    _currentBoss = boss;
    return boss;
}

Registry &Game::getRegistry()
{
    return _registry;
}

void Game::initializeComponents()
{
    _registry.register_component<Collision>();
    _registry.register_component<EntityTag>();
    _registry.register_component<Health>();
    _registry.register_component<Motion>();
    _registry.register_component<Position>();
    _registry.register_component<Laser>();
}

void Game::initializeSystems()
{
    _registry.add_update_system<Position, Motion, EntityTag>(
        Systems::movement_system);
    _registry.add_update_system<Collision, EntityTag>(
        Systems::collision_system);
    _registry.add_update_system<Position, EntityTag>(Systems::cleanup_system);
}
