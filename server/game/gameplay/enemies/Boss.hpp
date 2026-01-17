/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** game
*/

#ifndef BOSS_HPP
#define BOSS_HPP

#include "AEnemy.hpp"
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

class Boss : public AEnemy
{
  public:
    Boss(NetworkManager &nm, Registry &r, EntityFactory &factory,
         std::chrono::steady_clock::time_point gameStart, BossConfig bc,
         int difficulty = 1);
    ~Boss() = default;
    void shoot() override;

    void setPatterns(const std::vector<PatternType> &patterns);
    int getDifficulty() const;

  private:
    void bulletPattern();
    void rotatePattern();
    void patternRadialBurst();
    void patternSpiral();
    void patternWaveSpread();
    void patternDoubleSpiral();
    void patternFlower();

    std::chrono::steady_clock::time_point _start;
    std::chrono::steady_clock::time_point _patternChangeTime;

    std::vector<PatternType> _patterns;
    int _difficulty;
    std::size_t _currentPatternIndex;
    float _patternRotation;
};

#endif /* BOSS_HPP */
