#include "GameBoss.hpp"
#include "Game.hpp"
#include "ecs/entity/Entity.hpp"
#include "network/logger/Logger.hpp"
#include "network/packets/impl/GameOverPacket.hpp"
#include "network/packets/impl/HitboxSizeUpdatePacket.hpp"
#include "shared/components/HitBox.hpp"
#include "shared/components/Position.hpp"
#include <chrono>
#include <memory>
#include <network/packets/Packet.hpp>
#include <network/packets/impl/NewBulletPacket.hpp>
#include <network/packets/impl/NewEnemyPacket.hpp>

GameBoss::GameBoss(Game &game)
    : _game(game), _start(std::chrono::steady_clock::now())
{
}

void GameBoss::update()
{
    if (!_game.isRunning())
        return;

    if (_state == waiting) {
        auto now = std::chrono::steady_clock::now();
        auto elapsed =
            std::chrono::duration_cast<std::chrono::milliseconds>(now - _start);
        if (elapsed.count() > 2000) {
            this->initWave();
        }
    } else if (_state == active) {
        this->shoot();
        this->checkWaveCompletion();
    }
}

void GameBoss::initWave()
{
    if (_curWave >= _maxWaves) {
        LOG("Victory!");
        _game.sendPackets(std::make_shared<GameOverPacket>(EndGameState::WIN));
        _game.stop();
        return;
    }
    LOG("Starting wave " << (_curWave + 1) << " / " << _maxWaves);
    for (int i = 0; i < _nbEnemyPerWave[_curWave]; i++) {
        this->spawnEnemy();
    }
    this->spawnBoss();
    _state = active;
}

void GameBoss::spawnEnemy()
{
    Entity enemy = _game.getFactory().createEnemy(static_cast<int>(_curWave));
    _game.sendPackets(std::make_shared<NewEnemyPacket>(enemy.getId()));

    auto hitBox = _game.getRegistry().get<HitBox>(enemy.getId());
    if (hitBox.has_value()) {
        std::shared_ptr<Packet> HitBoxSize =
            create_packet(HitboxSizeUpdatePacket, enemy.getId(), hitBox->width,
                          hitBox->height);
        _game.sendPackets(HitBoxSize);
    }
    _enemies.emplace(enemy.getId(), std::chrono::steady_clock::now());
}

void GameBoss::spawnBoss()
{
    Entity boss = _game.getFactory().createBoss(static_cast<int>(_curWave));
    _game.sendPackets(std::make_shared<NewEnemyPacket>(boss.getId()));

    auto hitBox = _game.getRegistry().get<HitBox>(boss.getId());
    if (hitBox.has_value()) {
        std::shared_ptr<Packet> HitBoxSize =
            create_packet(HitboxSizeUpdatePacket, boss.getId(), hitBox->width,
                          hitBox->height);
        _game.sendPackets(HitBoxSize);
    }
    _bosses.emplace(boss.getId(), std::chrono::steady_clock::now());
}

bool GameBoss::isWaveComplete()
{
    return _enemies.empty() && _bosses.empty();
}

void GameBoss::checkWaveCompletion()
{
    if (isWaveComplete() && _state == active) {
        LOG("Wave " << (_curWave + 1) << " completed!");
        _curWave++;
        _state = waiting;
        _start = std::chrono::steady_clock::now();
    }
}

void GameBoss::removeEnemy(std::size_t id)
{
    _enemies.erase(id);
}

void GameBoss::removeBoss(std::size_t id)
{
    _bosses.erase(id);
}

void GameBoss::shoot()
{
    if (!_game.isRunning())
        return;

    auto now = std::chrono::steady_clock::now();

    for (auto it = _bosses.begin(); it != _bosses.end();) {
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            now - it->second);

        auto bossPos = _game.getRegistry().get<Position>(it->first);
        if (!bossPos.has_value()) {
            it = _bosses.erase(it);
            continue;
        }

        if (elapsed.count() >= 500) {
            auto bullet = _game.getFactory().createBossBullet(
                static_cast<int>(it->first), bossPos->x, bossPos->y);
            _game.sendPackets(std::make_shared<NewBulletPacket>(bullet.getId()));

            auto hitBox = _game.getRegistry().get<HitBox>(bullet.getId());
            if (hitBox.has_value()) {
                _game.sendPackets(create_packet(HitboxSizeUpdatePacket,
                                                bullet.getId(), hitBox->width,
                                                hitBox->height));
            }
            it->second = now;
        }
        ++it;
    }
    for (auto it = _enemies.begin(); it != _enemies.end();) {
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            now - it->second);

        auto enemyPos = _game.getRegistry().get<Position>(it->first);
        if (!enemyPos.has_value()) {
            it = _enemies.erase(it);
            continue;
        }

        if (elapsed.count() >= 1000) {
            auto bullet = _game.getFactory().createEnemyBullet(
                static_cast<int>(it->first), enemyPos->x, enemyPos->y);
            _game.sendPackets(std::make_shared<NewBulletPacket>(bullet.getId()));

            auto hitBox = _game.getRegistry().get<HitBox>(bullet.getId());
            if (hitBox.has_value()) {
                _game.sendPackets(create_packet(HitboxSizeUpdatePacket,
                                                bullet.getId(), hitBox->width,
                                                hitBox->height));
            }
            it->second = now;
        }
        ++it;
    }
}
