#include "GameBoss.hpp"
#include "Game.hpp"
#include "shared/components/Position.hpp"
#include <chrono>
#include <memory>
#include <network/packets/Packet.hpp>
#include <network/packets/impl/NewBulletPacket.hpp>
#include <network/packets/impl/NewEnemyPacket.hpp>

GameBoss::GameBoss(Game &game)
    : _game(game), _lastShoot(std::chrono::steady_clock::now())
{
}

void GameBoss::update()
{
    if (!this->hasBoss()) {
        this->newBoss();
    } else {
        this->shoot();
    }
}

bool GameBoss::hasBoss()
{
    return _curBoss.has_value();
}

bool GameBoss::newBoss()
{
    _curBoss = this->_game.getFactory().createBoss();
    this->_game.sendPackets(
        std::make_shared<NewEnemyPacket>(_curBoss->getId()));
    return true;
}

bool GameBoss::shoot()
{
    auto now = std::chrono::steady_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastShoot);

    if (elapsed.count() < 500) {
        return false;
    }
    auto boss = _game.getRegistry().get<Position>(_curBoss->getId());
    if (!boss.has_value()) {
        _curBoss.reset();
        return false;
    }
    auto e = this->_game.getFactory().createBossBullet(
        static_cast<int>(_curBoss->getId()), boss->x, boss->y);
    this->_game.sendPackets(std::make_shared<NewBulletPacket>(e.getId()));
    _lastShoot = now;
    return true;
}
