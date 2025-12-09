#include "GameSystems.hpp"
#include "server/components/Position.hpp"
#include "server/components/EntityType.hpp"
#include "server/components/Motion.hpp"
#include <iostream>

auto Systems::movement_system(
    [[maybe_unused]] Registry &r,
    std::unordered_map<std::size_t, std::tuple<Position, Motion, EntityTag>>
        items) -> void
{
    for (auto &&[i, item] : items) {
        EntityTag &tag = std::get<EntityTag>(item);
        Position &position = std::get<Position>(item);
        Motion &motion = std::get<Motion>(item);
        if (tag.type == EntityType::PLAYER) {
            // special case for user input
            std::cout << "player\n";
        } else {
            std::cout << "other\n";
            position.x += motion.velocity_x;
            position.y += motion.velocity_y;
            motion.velocity_x += motion.acceleration_x;
            motion.velocity_y += motion.acceleration_y;
        }
    }
}

auto Systems::collision_system(
    [[maybe_unused]] Registry &r,
    std::unordered_map<std::size_t, std::tuple<Collision, EntityTag>> items)
    -> void
{
    // check collision and sub health to player and boss
    for (auto &&[i, item] : items) {
        [[maybe_unused]] EntityTag &tag = std::get<EntityTag>(item);
    }
}

auto Systems::cleanup_system(
    [[maybe_unused]] Registry &r,
    std::unordered_map<std::size_t, std::tuple<Position, EntityTag>> items)
    -> void
{
    // check if it's a bullet and not on window anymore
    for (auto &&[i, item] : items) {
        [[maybe_unused]] EntityTag &tag = std::get<EntityTag>(item);
        // if not on window:
        // r.kill_entity(r.entity_from_index(i));
    }
}
