#include "EntityFactory.hpp"

EntityFactory::EntityFactory(Registry &registry) : _registry(registry) {}

Entity EntityFactory::createPlayer(void)
{
    Entity player = _registry.spawn_entity();

    _registry.emplace_component<Position>(player, 0.0, 0.0);
    return player;
}

Entity EntityFactory::createBoss(void)
{
    Entity boss = _registry.spawn_entity();

    _registry.emplace_component<Position>(boss, 0.0, 0.0);
    return boss;
}

Entity EntityFactory::createPlayerLaser(void) 
{
    Entity playerLaser = _registry.spawn_entity();

    _registry.emplace_component<Position>(playerLaser, 0.0, 0.0);
    return playerLaser;
}

Entity EntityFactory::createBossBullet(void) 
{
    Entity bossBullet = _registry.spawn_entity();

    _registry.emplace_component<Position>(bossBullet, 0.0, 0.0);
    return bossBullet;
}
