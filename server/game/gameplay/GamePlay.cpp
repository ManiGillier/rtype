#include "GamePlay.hpp"
#include "network/logger/Logger.hpp"
#include "network/packets/impl/NewEnemyPacket.hpp"
#include "server/game/components/Pattern.hpp"
#include "server/game/factories/EntityFactory.hpp"
#include "server/game/gameplay/GameConfig.hpp"
#include "server/game/gameplay/WaveConfigLoader.hpp"
#include "server/game/gameplay/enemies/Boss.hpp"
#include "server/game/gameplay/enemies/Enemy.hpp"
#include "shared/components/Position.hpp"
#include <algorithm>
#include <memory>

GamePlay::GamePlay(NetworkManager &nm, Registry &r, EntityFactory &factory,
                   const std::string &configPath)
    : _networkManager(nm), _regisrty(r), _factory(factory)
{
    _state = GameState::waiting;
    _currentWave = 0;
    _start = std::chrono::steady_clock::now();
    _gameStartTime = std::chrono::steady_clock::now();

    if (!loadConfig(configPath)) {
        LOG_ERR("Failed to load config");
        loadDefaultWaves();
    }
}

int GamePlay::getCurrentWave() const
{
    return _currentWave;
}

int GamePlay::getCurrentDifficulty() const
{
    if (_currentWave < static_cast<int>(_waves.size())) {
        return _waves[_currentWave].difficulty;
    }
    return 1;
}

bool GamePlay::loadConfig(const std::string &configPath)
{
    if (!_configLoader.load(configPath))
        return false;

    _waves = _configLoader.getWaves();
    _maxWaveNb = _configLoader.getMaxWaves();
    return true;
}

void GamePlay::loadDefaultWaves()
{
    _maxWaveNb = 8;
    BossConfig bc = {
        .pv = 200,
        .size = 80,
        .healer = 50,
        .patternX = 50.0f,
        .patternY = 20.0f,
        .damagePerBullet = 15,
        .bulletSize = 10.0f,
        .speed = 1.0f,
        .type = EnemyType::Boss
    };
    _waves.push_back({1, {PatternType::SPIRAL}, 750, 1, bc});
    _waves.push_back({1, {PatternType::RADIAL_BURST}, 1000, 1, bc});
    _waves.push_back({2, {PatternType::AIMED_SHOT}, 500, 1, bc});
    _waves.push_back({2, {PatternType::WAVE_SPREAD, PatternType::SPIRAL}, 500, 1, bc});
    _waves.push_back({2, {PatternType::DOUBLE_SPIRAL}, 500, 1, bc});
    _waves.push_back({3, {PatternType::FLOWER, PatternType::AIMED_SHOT}, 500, 1, bc});
    _waves.push_back({3, {PatternType::RADIAL_BURST, PatternType::DOUBLE_SPIRAL}, 500, 1, bc});
    _waves.push_back({3, {PatternType::FLOWER, PatternType::WAVE_SPREAD, PatternType::SPIRAL}, 500, 1, bc});
}

WaveConfig GamePlay::getWaveConfig(int wave)
{
    if (wave < static_cast<int>(_waves.size()))
        return _waves[wave];

    BossConfig bc = {
        .pv = 200,
        .size = 80,
        .healer = 50,
        .patternX = 20,
        .patternY = 20,
        .damagePerBullet = 15,
        .bulletSize = 10.0f,
        .speed = 1.0f,
        .type = EnemyType::Boss
    };
    std::vector<PatternType> allPatterns = {
        PatternType::SPIRAL,        PatternType::RADIAL_BURST,
        PatternType::AIMED_SHOT,    PatternType::WAVE_SPREAD,
        PatternType::DOUBLE_SPIRAL, PatternType::FLOWER};
    return {1, allPatterns, 1, 1000, bc};
}

bool GamePlay::update()
{
    this->removeDeadBoss();
    if (this->gameOver())
        return true;

    auto now = std::chrono::steady_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(now - _start);

    if (_state == GameState::waiting &&
        elapsed.count() > getWaveConfig(_currentWave).waitTime) {
        this->spawnBoss();
        this->_state = GameState::active;
    } else if (_state == GameState::active) {
        for (auto &it : _enemies)
            it->shoot();
        if (_enemies.empty())
            nextWave();
    }
    return false;
}

bool GamePlay::gameOver()
{
    if (_currentWave >= _maxWaveNb) {
        _networkManager.queuePacket(
            std::make_shared<GameOverPacket>(EndGameState::WIN));
        return true;
    }
    return false;
}

void GamePlay::spawnBoss()
{
    WaveConfig config = getWaveConfig(_currentWave);

    auto boss = std::make_unique<Boss>(_networkManager, _regisrty, _factory,
                                       _gameStartTime,config.bossConfig, config.difficulty);
    boss->setPatterns(config.patterns);
    this->_enemies.push_back(std::move(boss));

    for (std::size_t i = 0; i < config.enemyNb; i++) {
        this->_enemies.push_back(std::make_unique<Enemy>(
            _networkManager, _regisrty, _factory, _gameStartTime, config.bossConfig.toEnemy()));
    }
    this->checkPos();
}

void GamePlay::checkPos()
{
    constexpr float MIN_DISTANCE = 50.0f;
    constexpr float SEPARATION_OFFSET = 100.0f;

    for (std::size_t i = 0; i < _enemies.size(); ++i) {
        for (std::size_t j = i + 1; j < _enemies.size(); ++j) {
            auto pos_i = _regisrty.get<Position>(_enemies[i]->getId());
            auto pos_j = _regisrty.get<Position>(_enemies[j]->getId());

            if (!pos_i || !pos_j)
                continue;
            if (std::abs(pos_i->x - pos_j->x) <= MIN_DISTANCE) {
                float new_x = std::min(pos_i->x + SEPARATION_OFFSET,
                                       GameConstants::width - 50.0f);
                _regisrty.set<Position>(_enemies[i]->getId(), new_x, pos_i->y);
            }
        }
    }
}

void GamePlay::nextWave()
{
    _currentWave++;
    _state = GameState::waiting;
    _start = std::chrono::steady_clock::now();
}

void GamePlay::removeDeadBoss()
{
    for (auto it = _enemies.begin(); it != _enemies.end();) {
        auto bossPos = _regisrty.get<Pattern>(it->get()->getId());
        if (!bossPos.has_value())
            it = _enemies.erase(it);
        else
            ++it;
    }
}
