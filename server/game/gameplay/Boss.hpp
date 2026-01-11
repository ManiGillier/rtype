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
#include <vector>

enum class PatternType {
    RADIAL_BURST,
    SPIRAL,
    AIMED_SHOT,
    WAVE_SPREAD,
};

class Boss
{
  public:
    Boss(NetworkManager &nm, Registry &r, EntityFactory &factory,
         int difficulty = 1);
    ~Boss() = default;
    std::size_t getId() const;
    void shoot();
    void setPatterns(const std::vector<PatternType> &patterns);
    int getDifficulty() const;

  private:
    void sendBullet(Entity e);
    void bulletPattern();
    void rotatePattern();

    void patternRadialBurst();
    void patternSpiral();
    void patternAimedShot();
    void patternWaveSpread();

    NetworkManager &_networkManager;
    Registry &_regisrty;
    EntityFactory _factory;

    std::size_t _id;
    std::chrono::steady_clock::time_point _start;
    std::chrono::steady_clock::time_point _patternChangeTime;

    std::vector<PatternType> _patterns;
    int _difficulty;
    std::size_t _currentPatternIndex;
    float _patternRotation;
};

#endif /* BOSS_HPP */
