#include "GamePlay.hpp"
#include "../systems/GameSystems.hpp"
#include "server/game/factories/EntityFactory.hpp"
#include "server/game/gameplay/Boss.hpp"
#include "shared/components/Position.hpp"
#include <algorithm>
#include <memory>

GamePlay::GamePlay(NetworkManager &nm, Registry &r, EntityFactory &factory)
    : _networkManager(nm), _regisrty(r), _factory(factory),
      _state(GameState::waiting), _currentWave(0), _maxWaveNb(8)
{
    _start = std::chrono::steady_clock::now();
    setupWaves();
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

void GamePlay::setupWaves()
{
    _waves.push_back({1, {PatternType::RADIAL_BURST}, 1, 1000});
    _waves.push_back({1, {PatternType::SPIRAL}, 1, 750});
    _waves.push_back({2, {PatternType::AIMED_SHOT}, 1, 500});
    _waves.push_back(
        {2, {PatternType::WAVE_SPREAD, PatternType::SPIRAL}, 1, 500});
    _waves.push_back({2, {PatternType::DOUBLE_SPIRAL}, 1, 500});
    _waves.push_back({3, {PatternType::FLOWER, PatternType::AIMED_SHOT}, 1, 500});
    _waves.push_back(
        {3, {PatternType::RADIAL_BURST, PatternType::DOUBLE_SPIRAL}, 1, 500});
    _waves.push_back(
        {3, {PatternType::FLOWER, PatternType::WAVE_SPREAD, PatternType::SPIRAL}, 1, 500});
}

WaveConfig GamePlay::getWaveConfig(int wave)
{
    if (wave < static_cast<int>(_waves.size())) {
        return _waves[wave];
    }
    int difficulty = 3;
    std::vector<PatternType> allPatterns = {
        PatternType::RADIAL_BURST,  PatternType::SPIRAL,
        PatternType::AIMED_SHOT,    PatternType::WAVE_SPREAD,
        PatternType::DOUBLE_SPIRAL, PatternType::FLOWER};
    return {difficulty, allPatterns, 1, 2000};
}

bool GamePlay::update()
{
    this->removeDeadBoss();
    if (_currentWave >= _maxWaveNb) {
        _networkManager.queuePacket(
            std::make_shared<GameOverPacket>(EndGameState::WIN));
        return true;
    }

    if (_state == GameState::waiting) {
        auto now = std::chrono::steady_clock::now();
        auto elapsed =
            std::chrono::duration_cast<std::chrono::milliseconds>(now - _start);

        WaveConfig config = getWaveConfig(_currentWave);

        if (elapsed.count() > config.waitTime) {
            this->spawnBoss();
            this->_state = GameState::active;
        }
    } else if (_state == GameState::active) {
        for (auto &it : _bosses)
            it->shoot();
        if (_bosses.empty())
            nextWave();
    }
    return false;
}

void GamePlay::spawnBoss()
{
    WaveConfig config = getWaveConfig(_currentWave);

    for (std::size_t i = 0; i < config.bossNb; i++) {
        auto boss = std::make_unique<Boss>(_networkManager, _regisrty, _factory,
                                           config.difficulty);

        boss->setPatterns(config.patterns);
        this->_bosses.push_back(std::move(boss));
    }
    this->checkPos();
}

void GamePlay::checkPos()
{
    constexpr float MIN_DISTANCE = 50.0f;
    constexpr float SEPARATION_OFFSET = 100.0f;

    for (std::size_t i = 0; i < _bosses.size(); ++i) {
        for (std::size_t j = i + 1; j < _bosses.size(); ++j) {
            auto pos_i = _regisrty.get<Position>(_bosses[i]->getId());
            auto pos_j = _regisrty.get<Position>(_bosses[j]->getId());

            if (!pos_i || !pos_j)
                continue;
            if (std::abs(pos_i->x - pos_j->x) <= MIN_DISTANCE) {
                float new_x =  std::min(pos_i->x + SEPARATION_OFFSET,
                                     GameConstants::width - 50.0f);
                _regisrty.set<Position>(_bosses[i]->getId(), new_x, pos_i->y);
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
    for (auto it = _bosses.begin(); it != _bosses.end();) {
        auto bossPos = _regisrty.get<Position>(it->get()->getId());
        if (!bossPos.has_value())
            it = _bosses.erase(it);
        else
            ++it;
    }
}
