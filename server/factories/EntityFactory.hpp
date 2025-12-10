/*
 ** EPITECH PROJECT, 2025
 ** rtype
 ** File description:
 ** position component
 */

#ifndef ENTITY_FACTORY_HPP
#define ENTITY_FACTORY_HPP

#include "../../ecs/regisrty/Registry.hpp"

class EntityFactory
{
  public:
    EntityFactory(Registry &registry);
    ~EntityFactory() = default;

    Entity createPlayer(void);
    Entity createBoss(void);
    Entity createPlayerLaser(int id);
    Entity createBossBullet(int id);

  private:
    Registry &_registry;
};

#endif /* ENTITY_TYPE_HPP */
