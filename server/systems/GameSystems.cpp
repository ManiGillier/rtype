#include "GameSystems.hpp"
#include "../game/Game.hpp"
#include "ecs/sparse_array/SparseArray.hpp"
#include "network/packets/impl/DespawnPlayerPacket.hpp"
#include "network/packets/impl/LaserActiveUpdatePacket.hpp"
#include "server/components/BossTag.hpp"
#include "server/components/Damager.hpp"
#include "shared/components/Dependence.hpp"
#include "shared/components/Laser.hpp"
#include "shared/components/Position.hpp"
#include <memory>
#include <network/logger/Logger.hpp>
#include <network/packets/impl/DespawnBulletPacket.hpp>
#include <network/packets/impl/GameOverPacket.hpp>
#include <network/packets/impl/HealthUpdatePacket.hpp>
#include <network/packets/impl/PlayerDiedPacket.hpp>
#include <network/packets/impl/PositionUpdatePacket.hpp>
#include <vector>
#include <set>

namespace GameConstants
{
constexpr float width = 800;
constexpr float height = 600;
constexpr float PLAYER_SPEED = 5.0f;
} // namespace GameConstants

auto Systems::movement_system(
    [[maybe_unused]] Registry &r,
    containers::indexed_zipper<SparseArray<Position>, SparseArray<Velocity>,
                               SparseArray<Acceleration>,
                               SparseArray<OutsideBoundaries>>
        zipper,
    Game &game) -> void
{
    for (auto &&[i, pos, vel, acc, out] : zipper) {
        pos->x += vel->x;
        pos->y += vel->y;
        vel->x = acc->x;
        vel->y = acc->y;
        if (!out->canGoOutside && out->min == -1.0f) {
            if (pos->x < 0.0f)
                pos->x = 0.0f;
            if (pos->x > GameConstants::width)
                pos->x = GameConstants::width;
            if (pos->y < 0.0f)
                pos->y = 0.0f;
            if (pos->y > GameConstants::height)
                pos->y = GameConstants::height;
        } else if (!out->canGoOutside && out->min != -1.0f) {
            if (pos->x < out->min) {
                pos->x = out->min;
                vel->x = std::abs(vel->x);
                acc->x = std::abs(acc->x);
            } else if (pos->x > out->max) {
                pos->x = out->max;
                vel->x = -std::abs(vel->x);
                acc->x = -std::abs(acc->x);
            }
            if (pos->y < out->min) {
                pos->y = out->min;
                vel->y = std::abs(vel->y);
                acc->y = std::abs(acc->y);
            } else if (pos->y > out->max) {
                pos->y = out->max;
                vel->y = -std::abs(vel->y);
                acc->y = -std::abs(acc->y);
            }
        } else if (out->canGoOutside &&
                   (pos->x < 0.0f || pos->x > GameConstants::width ||
                    pos->y < 0.0f || pos->y > GameConstants::height)) {
            game.sendPackets(std::make_shared<DespawnBulletPacket>(i));
            r.kill_entity(r.entity_from_index(i));
            continue;
        }
        game.sendPackets(
            std::make_shared<PositionUpdatePacket>(i, pos->x, pos->y));
    }
}

auto Systems::update_laser_system(
    [[maybe_unused]] Registry &r,
    containers::indexed_zipper<SparseArray<Position>, SparseArray<Laser>>
        zipper,
    Game &game) -> void
{
    for (auto &&[i, pos, laser] : zipper) {
        game.sendPackets(create_packet(LaserActiveUpdatePacket, i,
                                       laser->active, laser->length));
    }
}

auto Systems::update_player_system(Registry &r,
                                   std::shared_ptr<ClientInputsPacket> packet,
                                   std::size_t id) -> void
{
    auto &positions = r.get_components<Position>();
    auto &velocities = r.get_components<Velocity>();
    auto &dependences = r.get_components<Dependence>();
    auto &lasers = r.get_components<Laser>();

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

    auto &pos = positions[id].value();

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
    LOG("position update");
}

auto Systems::collision_system([[maybe_unused]] Registry &r,
                               [[maybe_unused]] containers::indexed_zipper<
                                   SparseArray<Position>, SparseArray<HitBox>>
                                   zipper, Game &game) -> void
{
    std::vector<std::size_t> to_kill;

    for (auto &&[i, pos_i, hitbox_i] : zipper) {
        for (auto &&[j, pos_j, hitbox_j] : zipper) {
            if (i >= j)
                continue;

            bool collisionX = pos_i->x < pos_j->x + hitbox_j->width &&
                              pos_i->x + hitbox_i->width > pos_j->x;
            bool collisionY = pos_i->y < pos_j->y + hitbox_j->height &&
                              pos_i->y + hitbox_i->height > pos_j->y;

            if (collisionX && collisionY) {
                auto damager_i = r.get<Damager>(i);
                auto health_j = r.get<Health>(j);
                if (damager_i.has_value() && health_j.has_value()) {
                    auto dep_i = r.get<Dependence>(i);
                    if (dep_i.has_value() && dep_i->id == j)
                        continue;
                    auto laser_i = r.get<Laser>(i);
                    if (laser_i.has_value() && !laser_i->active)
                        continue;
                    if (!laser_i.has_value()) {
                        to_kill.push_back(i);
                    }

                    int damage = damager_i->damage;
                    // if (r.get<Resistance>(j).has_value()) {
                    //     damage = static_cast<int>(
                    //         static_cast<float>(damage) *
                    //         (1.0f - r.get<Resistance>(j)->ratio));
                    // }
                    r.set<Health>(j, health_j->pv - damage, 100);
                }

                auto damager_j = r.get<Damager>(j);
                auto health_i = r.get<Health>(i);
                if (damager_j.has_value() && health_i.has_value()) {
                    auto dep_j = r.get<Dependence>(j);
                    if (dep_j.has_value() && dep_j->id == i)
                        continue;

                    auto laser_j = r.get<Laser>(j);
                    if (laser_j.has_value() && !laser_j->active)
                        continue;
                    if (!laser_j.has_value()) {
                        to_kill.push_back(j);
                    }
                    int damage = damager_j->damage;
                    // if (r.get<Resistance>(i).has_value()) {
                    //     damage = static_cast<int>(
                    //         static_cast<float>(damage) *
                    //         (1.0f - r.get<Resistance>(i)->ratio));
                    // }
                    r.set<Health>(i, health_i->pv - damage, 100);
                }
            }
        }
    }
    // BORDEL REMOVE DUPLICATES !!!
    std::set<int> s( to_kill.begin(), to_kill.end() );
    to_kill.assign( s.begin(), s.end() );
    for (auto &it : to_kill) {
        game.sendPackets(std::make_shared<DespawnBulletPacket>(it));
        r.kill_entity(r.entity_from_index(it));
    }
}

auto Systems::cleanup_system(
    Registry &r, containers::indexed_zipper<SparseArray<Health>> zipper,
    [[maybe_unused]] Game &game) -> void
{
    std::vector<std::size_t> to_kill;

    for (auto &&[i, health] : zipper) {
        if (game.getPlayers().empty()) {
            LOG("all player died");
            game.sendPackets(
                std::make_shared<GameOverPacket>(EndGameState::LOST));
            game.stop();
            return;
        }
        if (health->pv <= 0) {
            auto bossTag = r.get<BossTag>(i);
            if (bossTag.has_value()) {
                if (bossTag->isBoss) {
                    LOG("Boss killed, all players get 50 HP");
                    for (const auto &[playerId, laserId] : game.getPlayers()) {
                        auto playerHealth = r.get<Health>(playerId);
                        if (playerHealth.has_value()) {
                            int newHealth = std::min(playerHealth->pv + 50, 100);
                            r.set<Health>(playerId, newHealth, 100);
                            game.sendPackets(std::make_shared<HealthUpdatePacket>(playerId, newHealth));
                        }
                    }
                    game.sendPackets(std::make_shared<DespawnPlayerPacket>(i));
                    game.getGameBoss().removeBoss(i);
                    to_kill.push_back(i);
                    // r.kill_entity(r.entity_from_index(i));
                } else {
                    game.sendPackets(std::make_shared<DespawnPlayerPacket>(i));
                    game.getGameBoss().removeEnemy(i);
                    to_kill.push_back(i);
                    // r.kill_entity(r.entity_from_index(i));
                }
                continue;
            }
            game.sendPackets(std::make_shared<PlayerDiedPacket>(i));
                    game.sendPackets(std::make_shared<DespawnPlayerPacket>(i));
            if (game.getPlayers().contains(i))
                game.getPlayers().erase(i);
            to_kill.push_back(i);
            // r.kill_entity(r.entity_from_index(i));
            continue;
        }
        game.sendPackets(std::make_shared<HealthUpdatePacket>(i, health->pv));
    }
    // BORDEL REMOVE DUPLICATES !!!
    std::set<int> s( to_kill.begin(), to_kill.end() );
    to_kill.assign( s.begin(), s.end() );
    for (auto &i : to_kill) {
        r.kill_entity(r.entity_from_index(i));
    }
}
