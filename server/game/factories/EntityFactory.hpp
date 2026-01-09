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

class EntityFactory
{
  public:
    EntityFactory(Registry &registry);
    ~EntityFactory() = default;
    Entity createPlayer(void);
    Entity createPlayerLaser(int id);
    Entity createBoss();
  Entity createBossBullet(int id, float x, float y, float acc_x, float acc_y);

      private : Registry &_registry;
};

#endif /* ENTITY_TYPE_HPP */
