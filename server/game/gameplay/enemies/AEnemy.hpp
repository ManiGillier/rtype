/*
 ** EPITECH PROJECT, 2025
 ** rtype
 ** File description:
 ** AEnemy
 */

#ifndef AENEMY_HPP
#define AENEMY_HPP

#include "ecs/entity/Entity.hpp"
#include "ecs/regisrty/Registry.hpp"
#include "server/game/factories/EntityFactory.hpp"
#include "server/network/network_manager/NetworkManager.hpp"
#include <network/packets/impl/SpawnStraightMovingEntityPacket.hpp>
#include <cstddef>

class AEnemy
{
  public:
    AEnemy(NetworkManager &networkManager, Registry &registry,
           EntityFactory &factory,
           std::chrono::steady_clock::time_point gameStart, BossConfig bc);
    virtual ~AEnemy() = default;

    virtual void shoot() = 0;
    std::size_t getId() const;
    void addBullet(float spawn_x, float spawn_y, float acc_x, float acc_y);
    void sendBullet();
    void clearBullet();

  protected:
    NetworkManager &_networkManager;
    Registry &_registry;
    EntityFactory &_factory;
    std::chrono::steady_clock::time_point _gameStart;
    BossConfig _bc;
    std::size_t _id;
    std::vector<StraightMovingEntity> _data;
};

#endif /* AENEMY_HPP */
