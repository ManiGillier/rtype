#include "EntityFactory.hpp"
#include "../components/Collision.hpp"
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
    _registry.emplace_component<Motion>(player, 5.0f, 5.0f, 0.5f, 0.5);
    _registry.emplace_component<Collision>(player, 32.0f, 32.0f);
    _registry.emplace_component<EntityTag>(player, EntityType::PLAYER);
    return player;
}

Entity EntityFactory::createBoss(void)
{
    Entity boss = _registry.spawn_entity();

    _registry.emplace_component<Position>(boss, 700.0f, 300.0f);
    _registry.emplace_component<Health>(boss, 1000, 1000);
    _registry.emplace_component<Motion>(boss, 5.0f, 5.0f, 0.5f, 0.5);
    _registry.emplace_component<Collision>(boss, 64.0f, 64.0f);
    _registry.emplace_component<EntityTag>(boss, EntityType::BOSS);
    return boss;
}

Entity EntityFactory::createPlayerLaser(int id)
{
    Entity playerLaser = _registry.spawn_entity();

    _registry.emplace_component<Position>(playerLaser, -10.0f, -10.0f);
    _registry.emplace_component<Motion>(playerLaser, 5.0f, 5.0f, 0.5f, 0.5);
    _registry.emplace_component<Collision>(playerLaser, 0.0f, 0.0f);
    _registry.emplace_component<EntityTag>(playerLaser,
                                           EntityType::PLAYER_LASER);
    _registry.emplace_component<Laser>(playerLaser, false, id);
    return playerLaser;
}

Entity EntityFactory::createBossBullet(void)
{
    Entity bossBullet = _registry.spawn_entity();

    _registry.emplace_component<Position>(bossBullet, 0.0f, 0.0f);
    _registry.emplace_component<Motion>(bossBullet, 5.0f, 5.0f, 0.5f, 0.5);
    _registry.emplace_component<Collision>(bossBullet, 12.0f, 12.0f);
    _registry.emplace_component<EntityTag>(bossBullet,
                                           EntityType::BOSS_BULLET);
    return bossBullet;
}
