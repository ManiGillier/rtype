#include "AEnemy.hpp"
#include "network/packets/impl/HitboxSizeUpdatePacket.hpp"
#include "server/game/components/Acceleration.hpp"
#include "server/game/factories/EntityFactory.hpp"
#include "shared/components/HitBox.hpp"
#include "shared/components/Position.hpp"
#include "server/game/components/Tag.hpp"
#include "server/game/factories/EntityFactory.hpp"
#include "server/game/gameplay/enemies/AEnemy.hpp"
#include "shared/components/HitBox.hpp"
#include "shared/components/Position.hpp"
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <math.h>

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
    sme.pos_x = static_cast<int16_t>(pos->x);
    sme.pos_y = static_cast<int16_t>(pos->y);
    sme.vel_x = static_cast<int16_t>(vel->x);
    sme.vel_y = static_cast<int16_t>(vel->y);

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

void AEnemy::patternAimedShot(int shotsByPlayer, int difficulty)
{
    auto hitBox = _registry.get<HitBox>(_id);
    auto pos = _registry.get<Position>(_id);

    if (!hitBox.has_value() || !pos.has_value())
        return;

    float center_x = pos->x;
    float center_y = pos->y;

    auto &positions = _registry.get_components<Position>();
    auto &tags = _registry.get_components<Tag>();

    std::vector<std::pair<float, float>> player_positions;

    for (std::size_t i = 0; i < positions.size() && i < tags.size(); ++i) {
        if (positions[i].has_value() && tags[i].has_value()) {
            if (tags[i]->tag == EntityTag::PLAYER) {
                player_positions.push_back({positions[i]->x, positions[i]->y});
            }
        }
    }

    if (player_positions.empty())
        return;

    int shots_per_player = shotsByPlayer + difficulty;
    float bullet_speed = 2.0f + (static_cast<float>(difficulty) * 0.3f);
    float spawn_radius = std::max(hitBox->width, hitBox->height) / 2.0f + 20.0f;

    for (const auto &player_pos : player_positions) {
        float dx = player_pos.first - center_x;
        float dy = player_pos.second - center_y;
        float base_angle = std::atan2(dy, dx);

        for (int i = 0; i < shots_per_player; i++) {
            float spread =
                (static_cast<float>(i - shots_per_player / 2)) * 0.15f;
            float angle = base_angle + spread;

            float acc_x = static_cast<float>(bullet_speed * std::cos(angle));
            float acc_y = static_cast<float>(bullet_speed * std::sin(angle));

            float spawn_x =
                center_x + spawn_radius * static_cast<float>(std::cos(angle));
            float spawn_y =
                center_y + spawn_radius * static_cast<float>(std::sin(angle));
            this->addBullet(spawn_x, spawn_y, acc_x, acc_y);
        }
    }
}
