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
#include <unordered_map>
#include <vector>

class Game;

enum WaveState { waiting = 0, active, completed };

class GameBoss
{
  public:
    GameBoss(Game &game);
    ~GameBoss() = default;
    void update();
    void removeEnemy(std::size_t id);
    void removeBoss(std::size_t id);

  private:
    bool isWaveComplete();
    void initWave();
    void spawnEnemy();
    void spawnBoss();
    void shoot();
    void checkWaveCompletion();

    Game &_game;
    std::chrono::steady_clock::time_point _start;
    WaveState _state = waiting;
    std::vector<int> _nbEnemyPerWave = {3, 4, 5, 6, 7, 8};
    std::size_t _curWave = 0;
    std::size_t _maxWaves = 6;

    // Track enemies and bosses
    std::unordered_map<std::size_t, std::chrono::steady_clock::time_point> _enemies;
    std::unordered_map<std::size_t, std::chrono::steady_clock::time_point> _bosses;
};

#endif /* BOSS_HPP */
