#include "EntityFactory.hpp"
#include "../components/Acceleration.hpp"
#include "../components/Damager.hpp"
#include "../components/Resistance.hpp"
#include "../components/Velocity.hpp"
#include "../../shared/components/Dependence.hpp"
#include "../../shared/components/Health.hpp"
#include "../../shared/components/HitBox.hpp"
#include "../../shared/components/Laser.hpp"
#include "../../shared/components/Position.hpp"

EntityFactory::EntityFactory(Registry &registry) : _registry(registry) {}

Entity EntityFactory::createPlayer(void)
{
    Entity player = _registry.spawn_entity();

    _registry.emplace_component<Position>(player, 50.0f, 300.0f);
    _registry.emplace_component<Velocity>(player, 50.0f, 300.0f);
    _registry.emplace_component<Acceleration>(player, 50.0f, 300.0f);
    _registry.emplace_component<Health>(player, 100, 100);
    _registry.emplace_component<Resistance>(player, 10.0f);
    _registry.emplace_component<HitBox>(player, 0.0f, 0.0f);
    return player;
}

Entity EntityFactory::createBoss(void)
{
    Entity boss = _registry.spawn_entity();

    _registry.emplace_component<Position>(boss, 50.0f, 300.0f);
    _registry.emplace_component<Velocity>(boss, 50.0f, 300.0f);
    _registry.emplace_component<Acceleration>(boss, 50.0f, 300.0f);
    _registry.emplace_component<Health>(boss, 100, 100);
    _registry.emplace_component<Resistance>(boss, 50.0f);
    _registry.emplace_component<HitBox>(boss, 0.0f, 0.0f);
    return boss;
}

Entity EntityFactory::createPlayerLaser(int id)
{
    Entity playerLaser = _registry.spawn_entity();

    _registry.emplace_component<Position>(playerLaser, 50.0f, 300.0f);
    _registry.emplace_component<Dependence>(playerLaser, id);
    _registry.emplace_component<Laser>(playerLaser, false);
    _registry.emplace_component<HitBox>(playerLaser, 0.0f, 0.0f);
    _registry.emplace_component<Damager>(playerLaser, 10);
    return playerLaser;
}

Entity EntityFactory::createBossBullet(int id)
{
    Entity bossBullet = _registry.spawn_entity();

    _registry.emplace_component<Position>(bossBullet, 50.0f, 300.0f);
    _registry.emplace_component<Velocity>(bossBullet, 50.0f, 300.0f);
    _registry.emplace_component<Acceleration>(bossBullet, 50.0f, 300.0f);
    _registry.emplace_component<Damager>(bossBullet, 10);
    _registry.emplace_component<HitBox>(bossBullet, 0.0f, 0.0f);
    _registry.emplace_component<Dependence>(bossBullet, id);
    return bossBullet;
}
