/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** game
*/

#ifndef GAMEPLAY_HPP
#define GAMEPLAY_HPP

#include "ecs/entity/Entity.hpp"
#include <unordered_map>
#include <vector>
#include <chrono>

class Game;

enum GameState { waiting = 0, active, completed };

class GamePlay
{
  public:
    GamePlay(Game &game, std::chrono::steady_clock::time_point start);
    ~GamePlay() = default;
    void update();

  private:
    Game &_game;
    std::chrono::steady_clock::time_point _start;
    GameState _state;
    void spawnBoss();
};

#endif /* GAMEPLAY_HPP */
