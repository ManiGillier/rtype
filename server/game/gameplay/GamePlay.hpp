/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** game
*/

#ifndef GAMEPLAY_HPP
#define GAMEPLAY_HPP

#include "ecs/entity/Entity.hpp"
#include "ecs/regisrty/Registry.hpp"
#include "server/network/network_manager/NetworkManager.hpp"
#include "../factories/EntityFactory.hpp"
#include "Boss.hpp"
#include <chrono>
#include <memory>
#include <vector>

enum GameState { waiting = 0, active, completed };

struct WaveConfig {
    int difficulty;
    std::vector<PatternType> patterns;
    std::size_t bossNb;
    int waitTime;
};

class GamePlay
{
  public:
    GamePlay(NetworkManager &nm, Registry &r, EntityFactory &factory);
    ~GamePlay() = default;
    bool update();
    int getCurrentWave() const;
    int getCurrentDifficulty() const;

  private:
    void spawnBoss();
    void checkPos();
    void removeDeadBoss();
    void setupWaves();
    void nextWave();
    WaveConfig getWaveConfig(int wave);

    NetworkManager &_networkManager;
    Registry &_regisrty;
    EntityFactory &_factory;

    std::chrono::steady_clock::time_point _start;
    GameState _state;

    std::vector<std::unique_ptr<Boss>> _bosses;
    int _currentWave;
    int _maxWaveNb;
    std::vector<WaveConfig> _waves;
};

#endif /* GAMEPLAY_HPP */
