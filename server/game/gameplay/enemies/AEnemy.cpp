#include "AEnemy.hpp"
#include "network/packets/impl/HitboxSizeUpdatePacket.hpp"
#include "server/game/components/Acceleration.hpp"
#include "server/game/factories/EntityFactory.hpp"
#include "shared/components/HitBox.hpp"
#include "shared/components/Position.hpp"

AEnemy::AEnemy(NetworkManager &networkManager, Registry &registry,
               EntityFactory &factory,
               std::chrono::steady_clock::time_point gameStart, BossConfig bc)
    : _networkManager(networkManager), _registry(registry), _factory(factory),
      _gameStart(gameStart), _bc(bc)
{
    Entity boss = _factory.createBoss(bc);
    auto hitBox = _registry.get<HitBox>(boss.getId());

    networkManager.queuePacket(std::make_shared<NewEnemyPacket>(boss.getId(), bc.type));

    if (hitBox.has_value()) {
        std::shared_ptr<Packet> HitBoxSize =
            create_packet(HitboxSizeUpdatePacket, boss.getId(), hitBox->width,
                          hitBox->height);
        networkManager.queuePacket(HitBoxSize);
    }
    _id = boss.getId();
}

std::size_t AEnemy::getId() const
{
    return _id;
}

void AEnemy::addBullet(float spawn_x, float spawn_y, float acc_x, float acc_y)
{
    StraightMovingEntity sme;

    Entity e = _factory.createBossBullet(BulletConfig{static_cast<int>(_id), spawn_x,
                                         spawn_y, acc_x, acc_y, _bc.damagePerBullet, _bc.bulletSize});

    auto vel = _registry.get<Acceleration>(e.getId());
    auto pos = _registry.get<Position>(e.getId());

    sme.id = static_cast<uint16_t>(e.getId());
    sme.pos_x = static_cast<uint16_t>(pos->x);
    sme.pos_y = static_cast<uint16_t>(pos->y);
    sme.vel_x = static_cast<uint16_t>(vel->x);
    sme.vel_y = static_cast<uint16_t>(vel->y);

    auto hitBox = _registry.get<HitBox>(e.getId());
    if (hitBox.has_value()) {
        sme.hitbox_x = static_cast<uint8_t>(hitBox.value().height);
        sme.hitbox_y = static_cast<uint8_t>(hitBox.value().width);
    }
    auto diff = std::chrono::steady_clock::now() - _gameStart;
    sme.ms_time = static_cast<uint32_t>(
        std::chrono::duration_cast<std::chrono::milliseconds>(diff).count());
    _data.push_back(sme);
}

void AEnemy::sendBullet()
{
    _networkManager.queuePacket(
        create_packet(SpawnStraightMovingEntityPacket, _data));
}

void AEnemy::clearBullet() 
{
    this->_data.clear();
}
