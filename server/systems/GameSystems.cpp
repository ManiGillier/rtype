#include "GameSystems.hpp"

auto Systems::movement_system([[maybe_unused]] Registry &r) -> void
{
    // for (auto &&[i, item] : items) {
    // std::cout << "other\n";
    // position.x += motion.velocity_x;
    // position.y += motion.velocity_y;
    // motion.velocity_x += motion.acceleration_x;
    // motion.velocity_y += motion.acceleration_y;
    // }
}

auto Systems::collision_system([[maybe_unused]] Registry &r) -> void
{
    // check collision and sub health to player and boss
    // for (auto &&[i, item] : items) {
    //     [[maybe_unused]] EntityTag &tag = std::get<EntityTag>(item);
    // }
}

auto Systems::cleanup_system([[maybe_unused]] Registry &r) -> void
{
    // check if it's a bullet and not on window anymore
    // for (auto &&[i, item] : items) {
    //     [[maybe_unused]] EntityTag &tag = std::get<EntityTag>(item);
        // if not on window:
        // r.kill_entity(r.entity_from_index(i));
    // }
}
