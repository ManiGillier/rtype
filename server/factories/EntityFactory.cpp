#include "EntityFactory.hpp"
#include "../../shared/components/Dependence.hpp"
#include "../../shared/components/Health.hpp"
#include "../../shared/components/HitBox.hpp"
#include "../../shared/components/Laser.hpp"
#include "../../shared/components/Position.hpp"
#include "../components/Acceleration.hpp"
#include "../components/BossTag.hpp"
#include "../components/Damager.hpp"
#include "../components/OutsideBoundaries.hpp"
#include "../components/Resistance.hpp"
#include "../components/Velocity.hpp"
#include <cstdlib>

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

Entity EntityFactory::createEnemy(int waveNumber)
{
    Entity enemy = _registry.spawn_entity();

    int baseHealth = 60 + (waveNumber * 20);
    float speed = 2.0f + (static_cast<float>(waveNumber + rand() % 20) * 0.3f);

    float randomX = 600.0f + static_cast<float>(rand() % 100);
    float bottomY = 300.0f + static_cast<float>(rand() % 300);

    _registry.emplace_component<Position>(enemy, randomX, bottomY);
    _registry.emplace_component<Velocity>(enemy, -speed, 0.0f);
    _registry.emplace_component<Acceleration>(enemy, -speed, 0.0f);
    _registry.emplace_component<OutsideBoundaries>(enemy, false, 50.0f, 750.0f);
    _registry.emplace_component<Health>(enemy, baseHealth, baseHealth);
    _registry.emplace_component<Resistance>(enemy, 5.0f);
    _registry.emplace_component<HitBox>(enemy, 30.0f, 30.0f);
    _registry.emplace_component<BossTag>(enemy, false);

    return enemy;
}

Entity EntityFactory::createBoss(int waveNumber)
{
    Entity boss = _registry.spawn_entity();

    int bossHealth = 200 + ( waveNumber * 100);
    float bossSpeed = 3.0f + (static_cast<float>(waveNumber + rand() % 20) * 0.3f);
    float randomX = 600.0f + static_cast<float>(rand() % 100);
    float bottomY = 500.0f;

    _registry.emplace_component<Position>(boss, randomX, bottomY);
    _registry.emplace_component<Velocity>(boss, -bossSpeed, 0.0f);
    _registry.emplace_component<Acceleration>(boss, -bossSpeed, 0.0f);
    _registry.emplace_component<OutsideBoundaries>(boss, false, 20.0f, 780.0f);
    _registry.emplace_component<Health>(boss, bossHealth, bossHealth);
    _registry.emplace_component<Resistance>(boss, 50.0f);
    _registry.emplace_component<HitBox>(boss, 80.0f, 80.0f);
    _registry.emplace_component<BossTag>(boss, true);

    return boss;
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

Entity EntityFactory::createBossBullet(int id, float x, float y)
{
    Entity bossBullet = _registry.spawn_entity();

    _registry.emplace_component<Position>(bossBullet, x, y);
    _registry.emplace_component<Velocity>(bossBullet, 0.0f, -8.0f);
    _registry.emplace_component<Acceleration>(bossBullet, 0.0f, -8.0f);
    _registry.emplace_component<OutsideBoundaries>(bossBullet, true, -1.0,
                                                   -1.0);
    _registry.emplace_component<Damager>(bossBullet, 15);
    _registry.emplace_component<HitBox>(bossBullet, 10.0f, 10.0f);
    _registry.emplace_component<Dependence>(bossBullet, id);
    return bossBullet;
}

Entity EntityFactory::createEnemyBullet(int id, float x, float y)
{
    Entity enemyBullet = _registry.spawn_entity();

    _registry.emplace_component<Position>(enemyBullet, x, y);
    _registry.emplace_component<Velocity>(enemyBullet, 0.0f, -6.0f);
    _registry.emplace_component<Acceleration>(enemyBullet, 0.0f, -6.0f);
    _registry.emplace_component<OutsideBoundaries>(enemyBullet, true, -1.0,
                                                   -1.0);
    _registry.emplace_component<Damager>(enemyBullet, 8);
    _registry.emplace_component<HitBox>(enemyBullet, 8.0f, 8.0f);
    _registry.emplace_component<Dependence>(enemyBullet, id);
    return enemyBullet;
}
