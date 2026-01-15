#include "EntityFactory.hpp"
#include "../components/Acceleration.hpp"
#include "../components/Damager.hpp"
#include "../components/Healer.hpp"
#include "../components/Hitable.hpp"
#include "../components/OutsideBoundaries.hpp"
#include "../components/Pattern.hpp"
#include "../components/Resistance.hpp"
#include "../components/Tag.hpp"
#include "../components/Velocity.hpp"
#include "../gameplay/GameConfig.hpp"
#include "shared/components/Dependence.hpp"
#include "shared/components/Health.hpp"
#include "shared/components/HitBox.hpp"
#include "shared/components/Laser.hpp"
#include "shared/components/Position.hpp"

EntityFactory::EntityFactory(Registry &registry) : _registry(registry) {}

Entity EntityFactory::createPlayer(void)
{
    Entity player = _registry.spawn_entity();

    _registry.emplace_component<Position>(player, GameConstants::width / 2,
                                          GameConstants::height / 2);
    _registry.emplace_component<Velocity>(player, 5.0f, 5.0f);
    _registry.emplace_component<Acceleration>(player, 0.0f, 0.0f);
    _registry.emplace_component<OutsideBoundaries>(player, false);
    _registry.emplace_component<Health>(player, 100, 100);
    _registry.emplace_component<Resistance>(player, 10.0f);
    _registry.emplace_component<HitBox>(player, 30.0f, 30.0f);
    _registry.emplace_component<Tag>(player, EntityTag::PLAYER);
    return player;
}

Entity EntityFactory::createPlayerLaser(int id)
{
    Entity playerLaser = _registry.spawn_entity();

    _registry.emplace_component<Position>(playerLaser, 50.0f, 300.0f);
    _registry.emplace_component<Dependence>(playerLaser, id);
    _registry.emplace_component<HitBox>(playerLaser, 1.0f, 2000.0f);
    _registry.emplace_component<Laser>(playerLaser, false, 0.0f);
    _registry.emplace_component<Damager>(playerLaser, 8);
    _registry.emplace_component<Tag>(playerLaser, EntityTag::LASER);
    return playerLaser;
}

Entity EntityFactory::createBoss()
{
    Entity boss = _registry.spawn_entity();

    float x =
        50.0f + static_cast<float>(
                    rand() % static_cast<int>(GameConstants::width - 100));
    float y = GameConstants::height - 150;

    _registry.emplace_component<Position>(boss, x, y);
    _registry.emplace_component<Acceleration>(boss, 1.0f * 1.0f, 1.0f * 1.0f);
    _registry.emplace_component<Health>(boss, 180, 180);
    _registry.emplace_component<Resistance>(boss, 50.0f);
    _registry.emplace_component<HitBox>(boss, 80.0f, 80.0f);
    _registry.emplace_component<Pattern>(boss, x - 50, y - 20, x + 50, y + 20,
                                         0.0f);
    _registry.emplace_component<Tag>(boss, EntityTag::BOSS);
    _registry.emplace_component<Healer>(boss, 25);
    _registry.emplace_component<Hitable>(boss, false);
    return boss;
}

Entity EntityFactory::createBossBullet(int id, float x, float y, float acc_x,
                                       float acc_y)
{
    Entity bossBullet = _registry.spawn_entity();

    _registry.emplace_component<Position>(bossBullet, x, y);
    _registry.emplace_component<Velocity>(bossBullet, 0.0f, 0.0f);
    _registry.emplace_component<Acceleration>(bossBullet, acc_x * 50.0f,
                                              acc_y * 50.0f);
    _registry.emplace_component<OutsideBoundaries>(bossBullet, true);
    _registry.emplace_component<Damager>(bossBullet, 15);
    _registry.emplace_component<HitBox>(bossBullet, 10.0f, 10.0f);
    _registry.emplace_component<Dependence>(bossBullet, id);
    _registry.emplace_component<Tag>(bossBullet, EntityTag::BULLET);
    return bossBullet;
}
