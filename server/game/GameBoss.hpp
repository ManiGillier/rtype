/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** game
*/

#ifndef BOSS_HPP
#define BOSS_HPP

#include "ecs/entity/Entity.hpp"
#include <chrono>
#include <optional>

class Game;

class GameBoss
{
  public:
    GameBoss(Game &game);
    ~GameBoss() = default;
    void update();

  private:
    bool hasBoss();
    bool newBoss();
    bool shoot();
    std::optional<Entity> _curBoss;
    int _waveNb;
    Game &_game;
    std::chrono::steady_clock::time_point _lastShoot;
};

#endif /* BOSS_HPP */
