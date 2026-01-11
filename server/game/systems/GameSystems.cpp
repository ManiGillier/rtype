#include "GameSystems.hpp"
#include "ecs/sparse_array/SparseArray.hpp"
#include "network/packets/impl/DespawnPlayerPacket.hpp"
#include "network/packets/impl/LaserActiveUpdatePacket.hpp"
#include "server/game/components/OutsideBoundaries.hpp"
#include "server/game/components/Tag.hpp"
#include "shared/components/Dependence.hpp"
#include "shared/components/Health.hpp"
#include "shared/components/Laser.hpp"
#include "shared/components/Position.hpp"
#include "../components/Healer.hpp"
#include <memory>
#include <network/logger/Logger.hpp>
#include <network/packets/impl/DespawnBulletPacket.hpp>
#include <network/packets/impl/GameOverPacket.hpp>
#include <network/packets/impl/HealthUpdatePacket.hpp>
#include <network/packets/impl/PlayerDiedPacket.hpp>
#include <network/packets/impl/PositionUpdatePacket.hpp>
#include <set>

namespace GameConstants
{
constexpr float width = 800;
constexpr float height = 600;
constexpr float PLAYER_SPEED = 3.0f;
} // namespace GameConstants

auto Systems::position_system(
    Registry &r,
    containers::indexed_zipper<SparseArray<Position>, SparseArray<Velocity>,
                               SparseArray<Acceleration>,
                               SparseArray<OutsideBoundaries>>
        zipper,
    NetworkManager &nm) -> void
{
    for (auto &&[i, pos, vel, acc, out] : zipper) {
        pos->x += vel->x;
        pos->y += vel->y;
        vel->x = acc->x;
        vel->y = acc->y;
        if (!out->canGoOutside) {
            if (pos->x < 0.0f)
                pos->x = 0.0f;
            if (pos->x > GameConstants::width)
                pos->x = GameConstants::width;
            if (pos->y < 0.0f)
                pos->y = 0.0f;
            if (pos->y > GameConstants::height)
                pos->y = GameConstants::height;
        } else if (out->canGoOutside &&
                   (pos->x < 0.0f || pos->x > GameConstants::width ||
                    pos->y < 0.0f || pos->y > GameConstants::height)) {
            nm.queuePacket(std::make_shared<DespawnBulletPacket>(i));
            r.kill_entity(r.entity_from_index(i));
            continue;
        }
        auto packet = std::make_shared<PositionUpdatePacket>(i, pos->x, pos->y);
        nm.queuePacket(packet, i, true);
    }
}

auto Systems::pattern_system(
    Registry &r,
    containers::indexed_zipper<SparseArray<Position>, SparseArray<Acceleration>,
                               SparseArray<Pattern>>
        zipper,
    NetworkManager &nm) -> void
{
    (void)r;

    for (auto &&[i, pos, acc, pat] : zipper) {
        const float speed = acc->x;
        if (!pos || !pat)
            continue;

        float width = pat->max_x - pat->min_x;
        float height = pat->max_y - pat->min_y;
        float perimeter = 2 * (width + height);

        static float progress = 0.0f;
        progress += speed;
        if (progress >= perimeter)
            progress -= perimeter;

        if (progress < width) {
            pos->x = pat->min_x + progress;
            pos->y = pat->min_y;
        } else if (progress < width + height) {
            pos->x = pat->max_x;
            pos->y = pat->min_y + (progress - width);
        } else if (progress < 2 * width + height) {
            pos->x = pat->max_x - (progress - width - height);
            pos->y = pat->max_y;
        } else {
            pos->x = pat->min_x;
            pos->y = pat->max_y - (progress - 2 * width - height);
        }
        auto packet = std::make_shared<PositionUpdatePacket>(i, pos->x, pos->y);
        nm.queuePacket(packet, i, true);
    }
}

auto Systems::update_laser_system(
    [[maybe_unused]] Registry &r,
    containers::indexed_zipper<SparseArray<Position>, SparseArray<Laser>>
        zipper,
    NetworkManager &nm) -> void
{
    for (auto &&[i, pos, laser] : zipper) {
        auto packet = create_packet(LaserActiveUpdatePacket, i, laser->active,
                                    laser->length);
        nm.queuePacket(packet, i, true);
    }
}

auto Systems::player_velocity_system(Registry &r,
                                     std::shared_ptr<ClientInputsPacket> packet,
                                     std::size_t id) -> void
{
    auto &positions = r.get_components<Position>();
    auto &velocities = r.get_components<Velocity>();

    if (positions.size() <= id || !positions[id].has_value())
        return;
    if (velocities.size() <= id || !velocities[id].has_value())
        return;

    auto inputs = packet->getInputs();
    auto &vel = velocities[id].value();

    if (inputs.value.left)
        vel.x -= GameConstants::PLAYER_SPEED;
    if (inputs.value.right)
        vel.x += GameConstants::PLAYER_SPEED;
    if (inputs.value.up)
        vel.y += GameConstants::PLAYER_SPEED;
    if (inputs.value.down)
        vel.y -= GameConstants::PLAYER_SPEED;

    Systems::player_laser_system(r, packet, id);
}

auto Systems::player_laser_system(Registry &r,
                                  std::shared_ptr<ClientInputsPacket> packet,
                                  std::size_t id) -> void
{
    auto &positions = r.get_components<Position>();
    auto &dependences = r.get_components<Dependence>();
    auto &lasers = r.get_components<Laser>();

    auto &pos = positions[id].value();
    auto inputs = packet->getInputs();

    for (std::size_t i = 0; i < dependences.size(); ++i) {
        if (dependences[i].has_value() && dependences[i].value().id == id) {
            if (i < positions.size() && positions[i].has_value()) {
                positions[i].value().x = pos.x;
                positions[i].value().y = pos.y;
            }
            if (i < lasers.size() && lasers[i].has_value()) {
                lasers[i].value().active = inputs.value.shoot;
                lasers[i].value().length = GameConstants::height - pos.y;
            }
        }
    }
}

auto Systems::collision_system(
    Registry &r,
    containers::indexed_zipper<SparseArray<Position>, SparseArray<HitBox>>
        zipper,
    NetworkManager &nm) -> void
{
    std::set<std::size_t> to_kill;

    for (auto &&[i, pos_i, hitbox_i] : zipper) {
        for (auto &&[j, pos_j, hitbox_j] : zipper) {
            if (i >= j)
                continue;

            bool collisionX =
                pos_i->x - hitbox_i->width / 2 <
                    pos_j->x + hitbox_j->width / 2 &&
                pos_i->x + hitbox_i->width / 2 > pos_j->x - hitbox_j->width / 2;

            bool collisionY = pos_i->y - hitbox_i->height / 2 <
                                  pos_j->y + hitbox_j->height / 2 &&
                              pos_i->y + hitbox_i->height / 2 >
                                  pos_j->y - hitbox_j->height / 2;

            if (collisionX && collisionY) {
                auto damager_i = r.get<Damager>(i);
                auto damager_j = r.get<Damager>(j);

                auto health_j = r.get<Health>(j);
                auto health_i = r.get<Health>(i);

                auto tag_i = r.get<Tag>(i);
                auto tag_j = r.get<Tag>(j);

                if (damager_i.has_value() && health_j.has_value()) {
                    auto dep_i = r.get<Dependence>(i);
                    auto laser_i = r.get<Laser>(i);

                    if ((dep_i.has_value() && dep_i->id == j) ||
                        (laser_i.has_value() && !laser_i->active))
                        continue;

                    if (tag_i->tag == EntityTag::BULLET)
                        to_kill.insert(i);

                    if ((tag_i->tag == EntityTag::BULLET &&
                         tag_j->tag == EntityTag::PLAYER) ||
                        (tag_i->tag == EntityTag::LASER &&
                         tag_j->tag == EntityTag::BOSS)) {
                        int damage = damager_i->damage;
                        r.set<Health>(j, health_j->pv - damage,
                                      health_j->max_pv);
                    }
                }
                if (damager_j.has_value() && health_i.has_value()) {
                    auto dep_j = r.get<Dependence>(j);
                    auto laser_j = r.get<Laser>(j);

                    if ((dep_j.has_value() && dep_j->id == i) ||
                        (laser_j.has_value() && !laser_j->active))
                        continue;

                    if (tag_j->tag == EntityTag::BULLET)
                        to_kill.insert(j);

                    if ((tag_j->tag == EntityTag::BULLET &&
                         tag_i->tag == EntityTag::PLAYER) ||
                        (tag_j->tag == EntityTag::LASER &&
                         tag_i->tag == EntityTag::BOSS)) {
                        int damage = damager_j->damage;
                        r.set<Health>(i, health_i->pv - damage,
                                      health_i->max_pv);
                    }
                }
            }
        }
    }
    for (auto &it : to_kill) {
        r.kill_entity(r.entity_from_index(it));
        nm.queuePacket(std::make_shared<DespawnBulletPacket>(it));
    }
}

auto Systems::heal_all_players_system(Registry &r, int heal)
    -> void
{
    auto zipper = containers::indexed_zipper(r.get_components<Tag>());

    for (auto &&[i, tag] : zipper) {
        if (tag->tag == EntityTag::PLAYER) {
            auto hl = r.get<Health>(i);
            r.set<Health>(i, hl->pv + heal, hl->max_pv);
        }
    }
}

auto Systems::health_system(
    Registry &r, containers::indexed_zipper<SparseArray<Health>> zipper,
    NetworkManager &nm) -> void
{
    for (auto &&[i, health] : zipper) {
        nm.queuePacket(std::make_shared<HealthUpdatePacket>(i, health->pv), i,
                       true);
        if (health->pv <= 0) {
            auto tag = r.get<Tag>(i);
            if (tag->tag == EntityTag::BOSS)
                heal_all_players_system(r, r.get<Healer>(i)->healer);
            nm.queuePacket(std::make_shared<DespawnPlayerPacket>(i));
            r.kill_entity(r.entity_from_index(i));
        }
    }
}

auto Systems::loose_system([[maybe_unused]] Registry &r,
                           containers::indexed_zipper<SparseArray<Tag>> zipper,
                           NetworkManager &nm, std::mutex &m, bool &run) -> void
{
    int remainingPlayers = 0;

    for (auto &&[i, tag] : zipper)
        if (tag->tag == EntityTag::PLAYER)
            remainingPlayers++;

    if (remainingPlayers == 0) {
        nm.queuePacket(std::make_shared<GameOverPacket>(EndGameState::LOST));
        m.lock();
        run = false;
        m.unlock();
    }
}
