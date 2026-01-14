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
#include <network/packets/impl/SpawnStraightMovingEntityPacket.hpp>
#include <vector>

enum class PatternType {
    RADIAL_BURST,
    SPIRAL,
    AIMED_SHOT,
    WAVE_SPREAD,
    DOUBLE_SPIRAL,
    FLOWER,
};

class Boss
{
  public:
    Boss(NetworkManager &nm, Registry &r, EntityFactory &factory,
         std::chrono::steady_clock::time_point _gameStart, int difficulty = 1);
    ~Boss() = default;
    std::size_t getId() const;
    void shoot();
    void setPatterns(const std::vector<PatternType> &patterns);
    int getDifficulty() const;

  private:
    void addBullet(float spawn_x, float spawn_y, float acc_x, float acc_y);
    void bulletPattern();
    void rotatePattern();

    void patternRadialBurst();
    void patternSpiral();
    void patternAimedShot();
    void patternWaveSpread();
    void patternDoubleSpiral();
    void patternFlower();

    NetworkManager &_networkManager;
    Registry &_regisrty;
    EntityFactory _factory;

    std::size_t _id;
    std::chrono::steady_clock::time_point _gameStart;
    std::chrono::steady_clock::time_point _start;
    std::chrono::steady_clock::time_point _patternChangeTime;

    std::vector<StraightMovingEntity> _data;
    std::vector<PatternType> _patterns;
    int _difficulty;
    std::size_t _currentPatternIndex;
    float _patternRotation;
};

#endif /* BOSS_HPP */
