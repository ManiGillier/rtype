#include "Enemy.hpp"
#include "server/game/components/Hitable.hpp"
#include "server/game/factories/EntityFactory.hpp"
#include "shared/components/Position.hpp"

Enemy::Enemy(NetworkManager &networkManager, Registry &registry,
                       EntityFactory &factory,
                       std::chrono::steady_clock::time_point gameStart, BossConfig bc)
    : AEnemy(networkManager, registry, factory, gameStart, bc)
{
}

void Enemy::shoot()
{
    auto enemyPos = _registry.get<Position>(_id);
    if (!enemyPos.has_value())
        return;

    auto now = std::chrono::steady_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(now - _start);

    int shootInterval = 1500;

    if (elapsed.count() > shootInterval) {
        this->clearBullet();
        _start = now;
        _registry.set<Hitable>(_id, true);
        this->addBullet(enemyPos->x, enemyPos->y, 0, -3);
        this->sendBullet();
    }
}
