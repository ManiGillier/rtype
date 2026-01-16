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

Entity EntityFactory::createBoss(BossConfig bc)
{
    Entity boss = _registry.spawn_entity();

    float x =
        50.0f + static_cast<float>(
                    rand() % static_cast<int>(GameConstants::width - 100));
    float y = GameConstants::height - 150;

    _registry.emplace_component<Position>(boss, x, y);
    _registry.emplace_component<Acceleration>(boss, bc.speed, bc.speed);
    _registry.emplace_component<Health>(boss, bc.pv, bc.pv);
    _registry.emplace_component<HitBox>(boss, bc.size, bc.size);
    _registry.emplace_component<Pattern>(boss, x - bc.patternX, y - bc.patternY,
                                         x + bc.patternX, y + bc.patternY,
                                         0.0f);
    _registry.emplace_component<Healer>(boss, bc.healer);
    _registry.emplace_component<Hitable>(boss, false);
    _registry.emplace_component<Tag>(boss, EntityTag::BOSS);
    return boss;
}

Entity EntityFactory::createBossBullet(BulletConfig buc)
{
    Entity bossBullet = _registry.spawn_entity();

    _registry.emplace_component<Position>(bossBullet, buc.x, buc.y);
    _registry.emplace_component<Velocity>(bossBullet, 0.0f, 0.0f);
    _registry.emplace_component<Acceleration>(bossBullet, buc.acc_x * 50.0f,
                                              buc.acc_y * 50.0f);
    _registry.emplace_component<OutsideBoundaries>(bossBullet, true);
    _registry.emplace_component<Damager>(bossBullet, buc.damagePerBullet);
    _registry.emplace_component<HitBox>(bossBullet, buc.bulletSize,
                                        buc.bulletSize);
    _registry.emplace_component<Dependence>(bossBullet, buc.id);
    _registry.emplace_component<Tag>(bossBullet, EntityTag::BULLET);
    return bossBullet;
}
