#include "EntityFactory.hpp"
#include "shared/components/Dependence.hpp"
#include "shared/components/Health.hpp"
#include "shared/components/HitBox.hpp"
#include "shared/components/Laser.hpp"
#include "shared/components/Position.hpp"
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

Entity EntityFactory::createPlayerLaser(int id)
{
    Entity playerLaser = _registry.spawn_entity();

    _registry.emplace_component<Position>(playerLaser, 50.0f, 300.0f);
    _registry.emplace_component<Dependence>(playerLaser, id);
    _registry.emplace_component<Laser>(playerLaser, false, 0.0f);
    _registry.emplace_component<HitBox>(playerLaser, 1.0f, 1200.0f);
    _registry.emplace_component<Damager>(playerLaser, 10);
    return playerLaser;
}
