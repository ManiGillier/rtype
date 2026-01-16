/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** Wave config
*/

#ifndef WAVE_CONFIG_HPP
#define WAVE_CONFIG_HPP

#include "server/game/factories/EntityFactory.hpp"
#include "server/game/gameplay/enemies/Boss.hpp"
#include <vector>

struct WaveConfig {
    int difficulty;
    std::vector<PatternType> patterns;
    int waitTime;
    std::size_t enemyNb;
    BossConfig bossConfig;
};

#endif /* WAVE_CONFIG_HPP */
