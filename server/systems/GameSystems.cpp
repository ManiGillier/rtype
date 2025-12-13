#include "GameSystems.hpp"
#include "shared/components/Position.hpp"

namespace GameConstants {
    constexpr float SCREEN_WIDTH = 1920.0f;
    constexpr float SCREEN_HEIGHT = 1080.0f;
    constexpr float ENEMY_SPAWN_INTERVAL = 2.0f;
    constexpr float BOSS_SHOOT_COOLDOWN = 1.5f;
    constexpr int MAX_ENEMIES = 20;
    constexpr float BOSS_DETECTION_RANGE = 800.0f;
    constexpr float PLAYER_SPEED = 5.0f;
}

auto Systems::movement_system(
    [[maybe_unused]] Registry &r,
    containers::indexed_zipper<SparseArray<Position>, SparseArray<Velocity>,
                               SparseArray<Acceleration>>
        zipper,
    [[maybe_unused]] PacketQueue &packets) -> void
{
    // TODO: update with new position get by server
    for (auto &&[i, pos, vel, acc] : zipper) {
        pos->x += vel->x;
        pos->y += vel->y;
        vel->x += acc->x;
        vel->y += acc->y;
    }
}

auto Systems::dependence_system(
    [[maybe_unused]] Registry &r,
    containers::indexed_zipper<SparseArray<Position>, SparseArray<Dependence>,
                               SparseArray<Laser>>
        zipper,
    [[maybe_unused]] PacketQueue &packets) -> void
{
    for (auto &&[i, pos, dep, laser] : zipper) {
        auto p_pos =
            r.get_components<Position>()[static_cast<std::size_t>(dep->id)];
        pos->x = p_pos->x;
        pos->y = p_pos->y;
    }
}

auto Systems::collision_system(
    [[maybe_unused]] Registry &r,
    containers::indexed_zipper<SparseArray<Position>, SparseArray<HitBox>>
        zipper,
    [[maybe_unused]] PacketQueue &packets) -> void
{
    auto &healths = r.get_components<Health>();
    auto &damagers = r.get_components<Damager>();
    auto &resistances = r.get_components<Resistance>();

    for (auto &&[i, pos_i, hitbox_i] : zipper) {
        for (auto &&[j, pos_j, hitbox_j] : zipper) {
            if (i >= j) continue;

            bool collisionX = pos_i->x < pos_j->x + hitbox_j->width &&
                              pos_i->x + hitbox_i->width > pos_j->x;
            bool collisionY = pos_i->y < pos_j->y + hitbox_j->height &&
                              pos_i->y + hitbox_i->height > pos_j->y;

            if (collisionX && collisionY) {
                if (damagers[i].has_value() && healths[j].has_value()) {
                    int damage = damagers[i]->damage;

                    if (resistances[j].has_value()) {
                        damage = static_cast<int>(static_cast<float>(damage) * (1.0f - resistances[j]->ratio));
                    }

                    healths[j]->pv -= damage;
                }
                if (damagers[j].has_value() && healths[i].has_value()) {
                    int damage = damagers[j]->damage;

                    if (resistances[i].has_value()) {
                        damage = static_cast<int>(static_cast<float>(damage) * (1.0f - resistances[i]->ratio));
                    }

                    healths[i]->pv -= damage;
                }
            }
        }
    }
}

auto Systems::cleanup_system(Registry &r,
                    containers::indexed_zipper<SparseArray<Health>> zipper,
                    [[maybe_unused]] PacketQueue &packets) -> void
{
    for (auto &&[i, health] : zipper) {
        if (health->pv <= 0)
            r.kill_entity(r.entity_from_index(i));
    }
}
