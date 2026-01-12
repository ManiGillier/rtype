#include "Boss.hpp"
#include "../factories/EntityFactory.hpp"
#include "ecs/entity/Entity.hpp"
#include "network/packets/impl/HitboxSizeUpdatePacket.hpp"
#include "server/game/components/Tag.hpp"
#include "shared/components/HitBox.hpp"
#include "shared/components/Position.hpp"
#include <cmath>
#include <cstdlib>
#include <math.h>

Boss::Boss(NetworkManager &nm, Registry &r, EntityFactory &factory,
           int difficulty)
    : _networkManager(nm), _regisrty(r), _factory(factory),
      _difficulty(difficulty), _currentPatternIndex(0), _patternRotation(0.0f)
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
    _patternChangeTime = std::chrono::steady_clock::now();
    _patterns = {PatternType::RADIAL_BURST};
}

std::size_t Boss::getId() const
{
    return _id;
}

int Boss::getDifficulty() const
{
    return _difficulty;
}

void Boss::setPatterns(const std::vector<PatternType> &patterns)
{
    if (!patterns.empty()) {
        _patterns = patterns;
        _currentPatternIndex = (std::rand() % static_cast<int>(patterns.size()));
    }
}

void Boss::shoot()
{
    // Check if boss entity still exists
    auto bossPos = _regisrty.get<Position>(_id);
    if (!bossPos.has_value())
        return;

    auto now = std::chrono::steady_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(now - _start);

    int shootInterval = 2000 - (_difficulty * 500);

    if (elapsed.count() > shootInterval) {
        this->bulletPattern();
        _start = now;
    }

    auto patternElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
        now - _patternChangeTime);

    int patternChangeInterval = std::max(7000 - (_difficulty * 600), 3000);

    if (patternElapsed.count() > patternChangeInterval &&
        _patterns.size() > 1) {
        this->rotatePattern();
        _patternChangeTime = now;
    }

    _patternRotation += 0.02f * static_cast<float>(_difficulty);
    if (_patternRotation > static_cast<float>(2.0 * M_PI))
        _patternRotation -= static_cast<float>(2.0 * M_PI);
}

void Boss::rotatePattern()
{
    if (_patterns.empty())
        return;
    _currentPatternIndex = (_currentPatternIndex + 1) % _patterns.size();
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
    if (_patterns.empty() || _currentPatternIndex >= _patterns.size())
        return;

    PatternType currentPattern = _patterns[_currentPatternIndex];

    switch (currentPattern) {
        case PatternType::RADIAL_BURST:
            patternRadialBurst();
            break;
        case PatternType::SPIRAL:
            patternSpiral();
            break;
        case PatternType::AIMED_SHOT:
            patternAimedShot();
            break;
        case PatternType::WAVE_SPREAD:
            patternWaveSpread();
            break;
        case PatternType::DOUBLE_SPIRAL:
            patternDoubleSpiral();
            break;
        case PatternType::FLOWER:
            patternFlower();
            break;
    }
}

void Boss::patternRadialBurst()
{
    auto hitBox = _regisrty.get<HitBox>(_id);
    auto pos = _regisrty.get<Position>(_id);

    if (!hitBox.has_value() || !pos.has_value())
        return;

    float center_x = pos->x;
    float center_y = pos->y;

    int bullet_count = 14 + _difficulty;
    float bullet_speed = 0.5f + (static_cast<float>(_difficulty) * 0.1f);
    int rings = 4 + (_difficulty / 2);

    float spawn_radius = std::max(hitBox->width, hitBox->height) / 2.0f + 20.0f;

    for (int x = 0; x < rings; x++) {
        for (int i = 0; i < bullet_count; i++) {
            double angle = (2.0 * M_PI * i) / bullet_count +
                           static_cast<double>(_patternRotation);

            float acc_x = static_cast<float>(bullet_speed * std::cos(angle));
            float acc_y = static_cast<float>(bullet_speed * std::sin(angle));

            float spawn_x =
                center_x + spawn_radius * static_cast<float>(std::cos(angle));
            float spawn_y =
                center_y + spawn_radius * static_cast<float>(std::sin(angle));

            this->sendBullet(_factory.createBossBullet(
                static_cast<int>(_id), spawn_x, spawn_y, acc_x, acc_y));
        }
        bullet_speed += 0.5f + (static_cast<float>(_difficulty) * 0.15f);
    }
}

void Boss::patternSpiral()
{
    auto hitBox = _regisrty.get<HitBox>(_id);
    auto pos = _regisrty.get<Position>(_id);

    if (!hitBox.has_value() || !pos.has_value())
        return;

    float center_x = pos->x;
    float center_y = pos->y;

    int arms = 3 + _difficulty;
    int bullets_per_arm = 7 + _difficulty;
    float bullet_speed = 1.5f + (static_cast<float>(_difficulty) * 0.3f);
    float spawn_radius = std::max(hitBox->width, hitBox->height) / 2.0f + 20.0f;

    for (int arm = 0; arm < arms; arm++) {
        float base_angle =
            static_cast<float>((2.0 * M_PI * arm) / arms) + _patternRotation;

        for (int i = 0; i < bullets_per_arm; i++) {
            float spiral_offset = 1 * (static_cast<float>(i) * 0.3f);
            float angle = base_angle + spiral_offset;

            float speed = bullet_speed + (static_cast<float>(i) * 0.1f);
            float acc_x = static_cast<float>(speed * std::cos(angle));
            float acc_y = static_cast<float>(speed * std::sin(angle));

            float spawn_x =
                center_x + spawn_radius * static_cast<float>(std::cos(angle));
            float spawn_y =
                center_y + spawn_radius * static_cast<float>(std::sin(angle));

            this->sendBullet(_factory.createBossBullet(
                static_cast<int>(_id), spawn_x, spawn_y, acc_x, acc_y));
        }
    }
}

void Boss::patternAimedShot()
{
    auto hitBox = _regisrty.get<HitBox>(_id);
    auto pos = _regisrty.get<Position>(_id);

    if (!hitBox.has_value() || !pos.has_value())
        return;

    float center_x = pos->x;
    float center_y = pos->y;

    auto &positions = _regisrty.get_components<Position>();
    auto &tags = _regisrty.get_components<Tag>();

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

    int shots_per_player = 4 + _difficulty;
    float bullet_speed = 2.0f + (static_cast<float>(_difficulty) * 0.3f);
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

            this->sendBullet(_factory.createBossBullet(
                static_cast<int>(_id), spawn_x, spawn_y, acc_x, acc_y));
        }
    }
}

void Boss::patternWaveSpread()
{
    auto hitBox = _regisrty.get<HitBox>(_id);
    auto pos = _regisrty.get<Position>(_id);

    if (!hitBox.has_value() || !pos.has_value())
        return;

    float center_x = pos->x;
    float center_y = pos->y;

    int waves = 3 + (_difficulty / 2);
    int bullets_per_wave = 11 + (_difficulty * 2);
    float bullet_speed = 1.0f + (static_cast<float>(_difficulty) * 0.2f);
    float spawn_radius = std::max(hitBox->width, hitBox->height) / 2.0f + 20.0f;

    for (int wave = 0; wave < waves; wave++) {
        for (int i = 0; i < bullets_per_wave; i++) {
            float t =
                static_cast<float>(i) / static_cast<float>(bullets_per_wave);
            float base_angle = static_cast<float>(M_PI) * t + _patternRotation;

            float wave_offset =
                static_cast<float>(std::sin(t * 4.0f * M_PI + wave)) * 0.5f;
            float angle = base_angle + wave_offset;

            float speed = bullet_speed + (static_cast<float>(wave) * 0.3f);
            float acc_x = static_cast<float>(speed * std::cos(angle));
            float acc_y = static_cast<float>(speed * std::sin(angle));

            float spawn_x =
                center_x + spawn_radius * static_cast<float>(std::cos(angle));
            float spawn_y =
                center_y + spawn_radius * static_cast<float>(std::sin(angle));

            this->sendBullet(_factory.createBossBullet(
                static_cast<int>(_id), spawn_x, spawn_y, acc_x, acc_y));
        }
    }
}

void Boss::patternDoubleSpiral()
{
    auto hitBox = _regisrty.get<HitBox>(_id);
    auto pos = _regisrty.get<Position>(_id);

    if (!hitBox.has_value() || !pos.has_value())
        return;

    float center_x = pos->x;
    float center_y = pos->y;

    int arms = 2 + (_difficulty / 2);
    int bullets_per_arm = 8 + _difficulty;
    float bullet_speed = 1.2f + (static_cast<float>(_difficulty) * 0.25f);
    float spawn_radius = std::max(hitBox->width, hitBox->height) / 2.0f + 20.0f;

    for (int arm = 0; arm < arms; arm++) {
        float base_angle_cw = static_cast<float>((2.0 * M_PI * arm) / arms) + _patternRotation;
        float base_angle_ccw = static_cast<float>((2.0 * M_PI * arm) / arms) - _patternRotation;

        for (int i = 0; i < bullets_per_arm; i++) {
            float spiral_offset = static_cast<float>(i) * 0.25f;

            float angle_cw = base_angle_cw + spiral_offset;
            float speed_cw = bullet_speed + (static_cast<float>(i) * 0.08f);
            float acc_x_cw = static_cast<float>(speed_cw * std::cos(angle_cw));
            float acc_y_cw = static_cast<float>(speed_cw * std::sin(angle_cw));
            float spawn_x_cw = center_x + spawn_radius * static_cast<float>(std::cos(angle_cw));
            float spawn_y_cw = center_y + spawn_radius * static_cast<float>(std::sin(angle_cw));
            this->sendBullet(_factory.createBossBullet(
                static_cast<int>(_id), spawn_x_cw, spawn_y_cw, acc_x_cw, acc_y_cw));

            float angle_ccw = base_angle_ccw - spiral_offset;
            float speed_ccw = bullet_speed + (static_cast<float>(i) * 0.08f);
            float acc_x_ccw = static_cast<float>(speed_ccw * std::cos(angle_ccw));
            float acc_y_ccw = static_cast<float>(speed_ccw * std::sin(angle_ccw));
            float spawn_x_ccw = center_x + spawn_radius * static_cast<float>(std::cos(angle_ccw));
            float spawn_y_ccw = center_y + spawn_radius * static_cast<float>(std::sin(angle_ccw));
            this->sendBullet(_factory.createBossBullet(
                static_cast<int>(_id), spawn_x_ccw, spawn_y_ccw, acc_x_ccw, acc_y_ccw));
        }
    }
}

void Boss::patternFlower()
{
    auto hitBox = _regisrty.get<HitBox>(_id);
    auto pos = _regisrty.get<Position>(_id);

    if (!hitBox.has_value() || !pos.has_value())
        return;

    float center_x = pos->x;
    float center_y = pos->y;

    int petals = 5 + _difficulty;
    int bullets_per_petal = 7 + _difficulty;
    float bullet_speed = 1.0f + (static_cast<float>(_difficulty) * 0.2f);
    float spawn_radius = std::max(hitBox->width, hitBox->height) / 2.0f + 20.0f;

    for (int petal = 0; petal < petals; petal++) {
        float base_angle = static_cast<float>((2.0 * M_PI * petal) / petals) + _patternRotation;

        for (int i = 0; i < bullets_per_petal; i++) {
            float t = static_cast<float>(i) / static_cast<float>(bullets_per_petal);
            float curve = static_cast<float>(std::sin(t * M_PI)) * 0.8f;
            float angle = base_angle + curve;

            float speed = bullet_speed * (1.0f + t * 0.5f);
            float acc_x = static_cast<float>(speed * std::cos(angle));
            float acc_y = static_cast<float>(speed * std::sin(angle));

            float spawn_x = center_x + spawn_radius * static_cast<float>(std::cos(angle));
            float spawn_y = center_y + spawn_radius * static_cast<float>(std::sin(angle));

            this->sendBullet(_factory.createBossBullet(
                static_cast<int>(_id), spawn_x, spawn_y, acc_x, acc_y));
        }
    }
}
