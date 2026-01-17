/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** wave loader
*/

#ifndef WAVE_CONFIG_LOADER_HPP
#define WAVE_CONFIG_LOADER_HPP

#include "server/game/gameplay/WaveConfig.hpp"
#include <libconfig.h++>
#include <string>
#include <vector>

class WaveConfigLoader
{
  public:
    WaveConfigLoader() = default;
    ~WaveConfigLoader() = default;
    bool load(const std::string &configPath);
    const std::vector<WaveConfig> &getWaves() const;
    int getMaxWaves() const;
    BossConfig getDefaultBossConfig() const;

  private:
    BossConfig parseBossConfig(const libconfig::Setting &setting);
    std::vector<PatternType> parsePatterns(const libconfig::Setting &setting);
    PatternType stringToPatternType(const std::string &str);
    std::vector<WaveConfig> _waves;
    int _maxWaves = 8;
    BossConfig _defaultBossConfig;
};

#endif /* WAVE_CONFIG_LOADER_HPP */
