/*
 ** EPITECH PROJECT, 2025
 ** rtype
 ** File description:
 ** Enemy class
 */

#ifndef BASICENEMY_HPP
#define BASICENEMY_HPP

#include "AEnemy.hpp"
#include "server/game/factories/EntityFactory.hpp"

class Enemy : public AEnemy
{
  public:
    Enemy(NetworkManager &networkManager, Registry &registry,
          EntityFactory &factory,
          std::chrono::steady_clock::time_point gameStart, BossConfig bc);
    ~Enemy() override = default;
    void shoot() override;

  private:
    std::chrono::steady_clock::time_point _start;
};

#endif /* BASICENEMY_HPP */
