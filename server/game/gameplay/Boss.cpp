#include "Boss.hpp"
#include "../factories/EntityFactory.hpp"
#include "ecs/entity/Entity.hpp"
#include "network/packets/impl/HitboxSizeUpdatePacket.hpp"
#include "shared/components/HitBox.hpp"
#include "shared/components/Position.hpp"
#include <math.h>

Boss::Boss(NetworkManager &nm, Registry &r, EntityFactory &factory)
    : _networkManager(nm), _regisrty(r), _factory(factory)
{
    Entity boss = _factory.createBoss();
    auto hitBox = _regisrty.get<HitBox>(boss.getId());

    nm.queuePacket(std::make_shared<NewEnemyPacket>(boss.getId()));
    if (hitBox.has_value()) {
        std::shared_ptr<Packet> HitBoxSize =
            create_packet(HitboxSizeUpdatePacket, boss.getId(), hitBox->width,
                          hitBox->height);
        nm.queuePacket(HitBoxSize);
    }
    _id = boss.getId();
    _start = std::chrono::steady_clock::now();
}

std::size_t Boss::getId() const
{
    return _id;
}

void Boss::shoot()
{
    auto now = std::chrono::steady_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(now - _start);
    if (elapsed.count() > 4000) {
        this->bulletPattern();
        _start = now;
    }
}

void Boss::sendBullet(Entity e)
{
    _networkManager.queuePacket(std::make_shared<NewBulletPacket>(e.getId()));

    auto hitBox = _regisrty.get<HitBox>(e.getId());
    if (hitBox.has_value()) {
        _networkManager.queuePacket(create_packet(
            HitboxSizeUpdatePacket, e.getId(), hitBox->width, hitBox->height));
    }
}

void Boss::bulletPattern()
{
    auto hitBox = _regisrty.get<HitBox>(_id);
    auto pos = _regisrty.get<Position>(_id);

    if (!hitBox.has_value() || !pos.has_value())
        return;

    float center_x = pos->x;
    float center_y = pos->y;

    const int bullet_count = 20;
    float bullet_speed = 1.0f;

    float spawn_radius = std::max(hitBox->width, hitBox->height) / 2.0f + 20.0f;

    for (int x = 0; x < 10; x++) {
        for (int i = 0; i < bullet_count; i++) {
            double angle = (2.0 * M_PI * i) / bullet_count;

            float acc_x = static_cast<float>(bullet_speed * std::cos(angle));
            float acc_y = static_cast<float>(bullet_speed * std::sin(angle));

            float spawn_x =
                center_x + spawn_radius * static_cast<float>(std::cos(angle));
            float spawn_y =
                center_y + spawn_radius * static_cast<float>(std::sin(angle));

            this->sendBullet(_factory.createBossBullet(
                static_cast<int>(_id), spawn_x, spawn_y, acc_x, acc_y));
        }
        bullet_speed += 0.7f;
    }
}
