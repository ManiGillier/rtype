/*
 ** EPITECH PROJECT, 2025
 ** rtype
 ** File description:
 ** position component
 */

#ifndef ENTITY_FACTORY_HPP
#define ENTITY_FACTORY_HPP

#include "../../ecs/regisrty/Registry.hpp"
#include "../components/Collision.hpp"
#include "../components/EntityType.hpp"
#include "../components/Health.hpp"
#include "../components/Motion.hpp"
#include "../components/Position.hpp"

class EntityFactory
{
  public:
    EntityFactory(Registry &registry);
    ~EntityFactory() = default;

    Entity createPlayer(void);
    Entity createBoss(void);
    Entity createPlayerLaser(void);
    Entity createBossBullet(void);

  private:
    Registry &_registry;
};

#endif /* ENTITY_TYPE_HPP */
