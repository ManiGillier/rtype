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
#include "server/game/gameplay/enemies/AEnemy.hpp"
#include "server/game/gameplay/WaveConfig.hpp"
#include "server/game/gameplay/WaveConfigLoader.hpp"
#include "server/network/network_manager/NetworkManager.hpp"
#include "../factories/EntityFactory.hpp"
#include "enemies/Boss.hpp"
#include <chrono>
#include <memory>
#include <string>
#include <vector>

enum GameState { waiting = 0, active};

class GamePlay
{
  public:
    GamePlay(NetworkManager &nm, Registry &r, EntityFactory &factory, int difficuly,
             const std::string &configPath = "server/config.cfg");
    ~GamePlay() = default;
    bool update();
    int getCurrentWave() const;
    int getCurrentDifficulty() const;

  private:
    void spawnBoss();
    void checkPos();
    void removeDeadBoss();
    bool loadConfig(const std::string &configPath);
    void loadDefaultWaves();
    void setGameDifficulty();
    void nextWave();
    WaveConfig getWaveConfig(int wave);
    bool gameOver();

    NetworkManager &_networkManager;
    Registry &_regisrty;
    EntityFactory &_factory;
    int _difficuly = 1;
    std::chrono::steady_clock::time_point _gameStartTime;

    std::chrono::steady_clock::time_point _start;
    GameState _state;

    std::vector<std::unique_ptr<AEnemy>> _enemies;
    int _currentWave;
    int _maxWaveNb;
    std::vector<WaveConfig> _waves;
    WaveConfigLoader _configLoader;
};

#endif /* GAMEPLAY_HPP */
