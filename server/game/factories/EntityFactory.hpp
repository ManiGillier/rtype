/*
 ** EPITECH PROJECT, 2025
 ** rtype
 ** File description:
 ** position component
 */

#ifndef ENTITY_FACTORY_HPP
#define ENTITY_FACTORY_HPP

#include "ecs/regisrty/Registry.hpp"

class EntityFactory
{
  public:
    EntityFactory(Registry &registry);
    ~EntityFactory() = default;

    Entity createPlayer(void);
    Entity createEnemy(int waveNumber);
    Entity createBoss(int waveNumber);
    Entity createPlayerLaser(int id);
    Entity createBossBullet(int id, float x, float y);
    Entity createEnemyBullet(int id, float x, float y);

  private:
    Registry &_registry;
};

#endif /* ENTITY_TYPE_HPP */
