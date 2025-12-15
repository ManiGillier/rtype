#include "GameSystems.hpp"
#include "../game/Game.hpp"
#include "shared/components/Dependence.hpp"
#include "shared/components/Position.hpp"
#include <memory>
#include <network/logger/Logger.hpp>
#include <network/packets/impl/PlayerDiedPacket.hpp>
#include <network/packets/impl/PositionUpdatePacket.hpp>

namespace GameConstants
{
constexpr float width = 800;
constexpr float height = 600;
// constexpr float ENEMY_SPAWN_INTERVAL = 2.0f;
// constexpr float BOSS_SHOOT_COOLDOWN = 1.5f;
// constexpr int MAX_ENEMIES = 20;
// constexpr float BOSS_DETECTION_RANGE = 800.0f;
constexpr float PLAYER_SPEED = 5.0f;
} // namespace GameConstants

auto Systems::movement_system(
    [[maybe_unused]] Registry &r,
    [[maybe_unused]] containers::indexed_zipper<
        SparseArray<Position>, SparseArray<Velocity>, SparseArray<Acceleration>>
        zipper,
    [[maybe_unused]] Game &game) -> void
{
    for (auto &&[i, pos, vel, acc] : zipper) {
        pos->x += vel->x;
        pos->y += vel->y;
        vel->x += acc->x;
        vel->y += acc->y;
        game.addPacketToSend(
            std::make_shared<PositionUpdatePacket>(i, pos->x, pos->y));
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

    vel.x = 0.0f;
    vel.y = 0.0f;

    if (inputs.value.left)
        vel.x -= GameConstants::PLAYER_SPEED;
    if (inputs.value.right)
        vel.x += GameConstants::PLAYER_SPEED;
    if (inputs.value.up)
        vel.y -= GameConstants::PLAYER_SPEED;
    if (inputs.value.down)
        vel.y += GameConstants::PLAYER_SPEED;

    auto &pos = positions[id].value();
    pos.x += vel.x;
    pos.y += vel.y;

    for (std::size_t i = 0; i < dependences.size(); ++i) {
        if (dependences[i].has_value() && dependences[i].value().id == id) {
            if (i < positions.size() && positions[i].has_value()) {
                positions[i].value().x = pos.x;
                positions[i].value().y = pos.y;
            }
            if (i < lasers.size() && lasers[i].has_value()) {
                lasers[i].value().active = inputs.value.shoot;
                lasers[i].value().length = GameConstants::height - pos.x;
            }
        }
    }
    LOG("position update");
}

auto Systems::collision_system(
    [[maybe_unused]] Registry &r,
    containers::indexed_zipper<SparseArray<Position>, SparseArray<HitBox>>
        zipper) -> void
{
    auto &healths = r.get_components<Health>();
    auto &damagers = r.get_components<Damager>();
    auto &resistances = r.get_components<Resistance>();

    for (auto &&[i, pos_i, hitbox_i] : zipper) {
        for (auto &&[j, pos_j, hitbox_j] : zipper) {
            if (i >= j)
                continue;

            bool collisionX = pos_i->x < pos_j->x + hitbox_j->width &&
                              pos_i->x + hitbox_i->width > pos_j->x;
            bool collisionY = pos_i->y < pos_j->y + hitbox_j->height &&
                              pos_i->y + hitbox_i->height > pos_j->y;

            if (collisionX && collisionY) {
                if (damagers[i].has_value() && healths[j].has_value()) {
                    int damage = damagers[i]->damage;

                    if (resistances[j].has_value()) {
                        damage =
                            static_cast<int>(static_cast<float>(damage) *
                                             (1.0f - resistances[j]->ratio));
                    }

                    healths[j]->pv -= damage;
                }
                if (damagers[j].has_value() && healths[i].has_value()) {
                    int damage = damagers[j]->damage;

                    if (resistances[i].has_value()) {
                        damage =
                            static_cast<int>(static_cast<float>(damage) *
                                             (1.0f - resistances[i]->ratio));
                    }

                    healths[i]->pv -= damage;
                }
            }
        }
    }
}

auto Systems::cleanup_system(
    Registry &r, containers::indexed_zipper<SparseArray<Health>> zipper,
    Game &game) -> void
{
    for (auto &&[i, health] : zipper) {
        if (health->pv <= 0) {
            r.kill_entity(r.entity_from_index(i));
            game.addPacketToSend(std::make_shared<PlayerDiedPacket>(i));
        }
    }
}
