/*
 ** EPITECH PROJECT, 2025
 ** rtype
 ** File description:
 ** position component
 */

#ifndef ENTITY_FACTORY_HPP
#define ENTITY_FACTORY_HPP

#include "ecs/entity/Entity.hpp"
#include "ecs/regisrty/Registry.hpp"
#include "network/packets/impl/NewEnemyPacket.hpp"

typedef struct BossConfig {
    int pv;
    float size;
    int healer;
    float patternX;
    float patternY;
    int damagePerBullet;
    float bulletSize;
    float speed;
    EnemyType type = EnemyType::Boss;

    BossConfig toEnemy()
    {
        BossConfig bc = {
            .pv = this->pv / 4,
            .size = this->size / 3,
            .healer = this->healer / 3,
            .patternX = this->patternX * 6,
            .patternY = this->patternY,
            .damagePerBullet = this->damagePerBullet * 2,
            .bulletSize = this->bulletSize * 3,
            .speed = this->speed * 4,
            .type = EnemyType::Enemy,
        };
        return bc;
    }
} BossConfig;

typedef struct BulletConfig {
    int id;
    float x;
    float y;
    float acc_x;
    float acc_y;
    int damagePerBullet;
    float bulletSize;
} BulletConfig;

class EntityFactory
{
  public:
    EntityFactory(Registry &registry);
    ~EntityFactory() = default;
    Entity createPlayer(void);
    Entity createPlayerLaser(int id);
    Entity createBoss(BossConfig boc);
    Entity createBossBullet(BulletConfig buc);
  private:
    Registry &_registry;
};

#endif /* ENTITY_TYPE_HPP */
