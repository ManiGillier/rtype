#include "Game.hpp"
#include "../components/Collision.hpp"
#include "../components/Control.hpp"
#include "../components/EntityType.hpp"
#include "../components/Health.hpp"
#include "../components/Motion.hpp"
#include "../components/Position.hpp"
#include "../components/Laser.hpp"

Game::Game() : _registry(), _factory(_registry), _isRunning(false)
{
    initializeComponents();
    initializeSystems();
}

void Game::start()
{
    if (!_isRunning)
        _isRunning = true;
}

void Game::update()
{
    if (!_isRunning)
        return;

    //...
    _registry.render();
}

Entity Game::addPlayer(const std::unique_ptr<Player>
                           &player /* Player *player (client abstraction) */)
{
    Entity pl = _factory.createPlayer();

    _players.emplace(player->getId(), std::move(pl));
    return pl;
}

void Game::removePlayer(const std::unique_ptr<Player>
                            &player /* Player *player (client abstraction) */)
{
    _players.erase(player->getId());
}

Registry &Game::getRegistry()
{
    return _registry;
}

void Game::initializeComponents()
{
    _registry.register_component<Collision>();
    _registry.register_component<Control>();
    _registry.register_component<EntityTag>();
    _registry.register_component<Health>();
    _registry.register_component<Motion>();
    _registry.register_component<Position>();
    _registry.register_component<Laser>();
}

void Game::initializeSystems() 
{
}
