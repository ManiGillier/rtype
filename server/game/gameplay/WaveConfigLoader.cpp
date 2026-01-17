#include "WaveConfigLoader.hpp"
#include "network/logger/Logger.hpp"

bool WaveConfigLoader::load(const std::string &configPath)
{
    libconfig::Config cfg;

    try {
        cfg.readFile(configPath.c_str());
    } catch (const libconfig::FileIOException &e) {
        LOG_ERR("Error reading config file: " << configPath);
        return false;
    } catch (const libconfig::ParseException &e) {
        LOG_ERR("Parse error at " << e.getFile() << ":" << e.getLine() << " - "
                                  << e.getError());
        return false;
    }

    try {
        // Load game settings
        const libconfig::Setting &root = cfg.getRoot();

        if (root.exists("game")) {
            const libconfig::Setting &game = root["game"];
            if (game.exists("max_waves"))
                _maxWaves = game["max_waves"];
        }
        if (root.exists("default_boss"))
            _defaultBossConfig = parseBossConfig(root["default_boss"]);

        if (!root.exists("waves")) {
            LOG_ERR("No waves defined");
            return false;
        }

        const libconfig::Setting &waves = root["waves"];
        _waves.clear();

        for (int i = 0; i < waves.getLength(); i++) {
            const libconfig::Setting &wave = waves[i];
            WaveConfig waveConfig;

            waveConfig.difficulty = wave["difficulty"];
            waveConfig.patterns = parsePatterns(wave["patterns"]);
            waveConfig.waitTime = wave["wait_time"];
            waveConfig.enemyNb =
                static_cast<std::size_t>(static_cast<int>(wave["enemy_count"]));

            if (wave.exists("boss"))
                waveConfig.bossConfig = parseBossConfig(wave["boss"]);
            else
                waveConfig.bossConfig = _defaultBossConfig;
            _waves.push_back(waveConfig);
        }

    } catch (const libconfig::SettingNotFoundException &e) {
        LOG_ERR("Setting not found: " << e.getPath());
        return false;
    } catch (const libconfig::SettingTypeException &e) {
        LOG_ERR("Setting type error: " << e.getPath());
        return false;
    }
    return true;
}

BossConfig WaveConfigLoader::parseBossConfig(const libconfig::Setting &setting)
{
    BossConfig bc;

    bc.pv = setting["pv"];
    bc.size = static_cast<float>(static_cast<double>(setting["size"]));
    bc.healer = setting["healer"];
    bc.patternX = static_cast<float>(static_cast<double>(setting["pattern_x"]));
    bc.patternY = static_cast<float>(static_cast<double>(setting["pattern_y"]));
    bc.damagePerBullet = setting["damage_per_bullet"];
    bc.bulletSize =
        static_cast<float>(static_cast<double>(setting["bullet_size"]));
    bc.speed = static_cast<float>(static_cast<double>(setting["speed"]));
    return bc;
}

std::vector<PatternType>
WaveConfigLoader::parsePatterns(const libconfig::Setting &setting)
{
    std::vector<PatternType> patterns;

    for (int i = 0; i < setting.getLength(); i++) {
        std::string patternStr = setting[i];
        patterns.push_back(stringToPatternType(patternStr));
    }
    return patterns;
}

PatternType WaveConfigLoader::stringToPatternType(const std::string &str)
{
    if (str == "RADIAL_BURST")
        return PatternType::RADIAL_BURST;
    if (str == "SPIRAL")
        return PatternType::SPIRAL;
    if (str == "AIMED_SHOT")
        return PatternType::AIMED_SHOT;
    if (str == "WAVE_SPREAD")
        return PatternType::WAVE_SPREAD;
    if (str == "DOUBLE_SPIRAL")
        return PatternType::DOUBLE_SPIRAL;
    if (str == "FLOWER")
        return PatternType::FLOWER;

    LOG_ERR("Unknown pattern type: " << str);
    return PatternType::SPIRAL;
}

const std::vector<WaveConfig> &WaveConfigLoader::getWaves() const
{
    return _waves;
}

int WaveConfigLoader::getMaxWaves() const
{
    return _maxWaves;
}

BossConfig WaveConfigLoader::getDefaultBossConfig() const
{
    return _defaultBossConfig;
}
