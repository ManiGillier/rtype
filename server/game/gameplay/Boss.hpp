/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** game
*/

#ifndef BOSS_HPP
#define BOSS_HPP

#include "ecs/entity/Entity.hpp"
#include "ecs/regisrty/Registry.hpp"
#include "server/game/factories/EntityFactory.hpp"
#include "server/network/network_manager/NetworkManager.hpp"

class Boss
{
  public:
    Boss(NetworkManager &nm, Registry &r, EntityFactory &factory);
    ~Boss() = default;
    void shoot();

  private:
    void sendBullet(Entity e);
    void bulletPattern();
    NetworkManager &_networkManager;
    Registry &_regisrty;
    EntityFactory _factory;
    std::size_t _id;
    std::chrono::steady_clock::time_point _start;
    std::chrono::steady_clock::time_point _lastShoot;

};

#endif /* BOSS_HPP */
