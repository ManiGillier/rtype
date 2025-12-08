#include "EntityFactory.hpp"
#include "../components/Collision.hpp"
#include "../components/Control.hpp"
#include "../components/EntityType.hpp"
#include "../components/Health.hpp"
#include "../components/Laser.hpp"
#include "../components/Motion.hpp"
#include "../components/Position.hpp"

EntityFactory::EntityFactory(Registry &registry) : _registry(registry) {}

Entity EntityFactory::createPlayer(void)
{
    Entity player = _registry.spawn_entity();

    _registry.emplace_component<Position>(player, 50.0f, 300.0f);
    _registry.emplace_component<Health>(player, 100, 100);
    _registry.emplace_component<Motion>(player, 5.0f, 0.5f);
    _registry.emplace_component<Collision>(player, 32.0f, 32.0f);
    _registry.emplace_component<EntityTag>(player, EntityType::PLAYER);
    _registry.emplace_component<Control>(player, 0);
    return player;
}

Entity EntityFactory::createBoss(void)
{
    Entity boss = _registry.spawn_entity();

    _registry.emplace_component<Position>(boss, 700.0f, 300.0f);
    _registry.emplace_component<Health>(boss, 1000, 1000);
    _registry.emplace_component<Motion>(boss, 2.0f, 0.3f);
    _registry.emplace_component<Collision>(boss, 64.0f, 64.0f);
    _registry.emplace_component<EntityTag>(boss, EntityType::BOSS);
    return boss;
}

Entity EntityFactory::createPlayerLaser(void)
{
    Entity playerLaser = _registry.spawn_entity();

    _registry.emplace_component<Position>(playerLaser, 0.0f, 0.0f);
    _registry.emplace_component<Motion>(playerLaser, 10.0f, 0.0f);
    _registry.emplace_component<Collision>(playerLaser, 16.0f, 4.0f);
    _registry.emplace_component<EntityTag>(playerLaser,
                                           EntityType::PLAYER_BULLET);
    _registry.emplace_component<Laser>(playerLaser, true);
    return playerLaser;
}

Entity EntityFactory::createBossBullet(void)
{
    Entity bossBullet = _registry.spawn_entity();

    _registry.emplace_component<Position>(bossBullet, 0.0f, 0.0f);
    _registry.emplace_component<Motion>(bossBullet, -8.0f, 0.0f);
    _registry.emplace_component<Collision>(bossBullet, 12.0f, 12.0f);
    _registry.emplace_component<EntityTag>(bossBullet,
                                           EntityType::ENEMY_BULLET);
    return bossBullet;
}
