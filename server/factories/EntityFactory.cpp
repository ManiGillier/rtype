#include "EntityFactory.hpp"
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

EntityFactory::EntityFactory(Registry &registry) : _registry(registry) {}

Entity EntityFactory::createPlayer(void)
{
    Entity player = _registry.spawn_entity();

    _registry.emplace_component<Position>(player, 400.0f, 300.0f);
    _registry.emplace_component<Velocity>(player, 5.0f, 5.0f);
    _registry.emplace_component<Acceleration>(player, 0.0f, 0.0f);
    _registry.emplace_component<OutsideBoundaries>(player, false, -1.0, -1.0);
    _registry.emplace_component<Health>(player, 100, 100);
    _registry.emplace_component<Resistance>(player, 10.0f);
    _registry.emplace_component<HitBox>(player, 30.0f, 30.0f);
    return player;
}

Entity EntityFactory::createBoss(void)
{
    Entity boss = _registry.spawn_entity();

    _registry.emplace_component<Position>(boss, 50.0f, 500.0f);
    _registry.emplace_component<Velocity>(boss, 3.0f, 0.0f);
    _registry.emplace_component<Acceleration>(boss, 3.0f, 0.0f);
    _registry.emplace_component<OutsideBoundaries>(boss, false, 20.0f, 780.0f);
    _registry.emplace_component<Health>(boss, 100, 100);
    _registry.emplace_component<Resistance>(boss, 50.0f);
    _registry.emplace_component<HitBox>(boss, 40.0f, 40.0f);
    return boss;
}

Entity EntityFactory::createPlayerLaser(int id)
{
    Entity playerLaser = _registry.spawn_entity();

    _registry.emplace_component<Position>(playerLaser, 50.0f, 300.0f);
    _registry.emplace_component<Dependence>(playerLaser, id);
    _registry.emplace_component<Laser>(playerLaser, false, 0.0f);
    _registry.emplace_component<HitBox>(playerLaser, 1200.0f, 5.0f);
    _registry.emplace_component<Damager>(playerLaser, 10);
    return playerLaser;
}

Entity EntityFactory::createBossBullet(int id, float x, float y)
{
    Entity bossBullet = _registry.spawn_entity();

    _registry.emplace_component<Position>(bossBullet, x, y);
    _registry.emplace_component<Velocity>(bossBullet, 0.0f, -10.0f);
    _registry.emplace_component<Acceleration>(bossBullet, 0.0f, -10.0f);
    _registry.emplace_component<OutsideBoundaries>(bossBullet, true, -1.0,
                                                   -1.0);
    _registry.emplace_component<Damager>(bossBullet, 10);
    _registry.emplace_component<HitBox>(bossBullet, 8.0f, 8.0f);
    _registry.emplace_component<Dependence>(bossBullet, id);
    return bossBullet;
}
