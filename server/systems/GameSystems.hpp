/*
 ** EPITECH PROJECT, 2025
 ** rtype
 ** File description:
 ** position component
 */

#ifndef COMP_POSITION_HPP
#define COMP_POSITION_HPP

#include "../../ecs/regisrty/Registry.hpp"
#include "../components/Collision.hpp"
#include "../components/EntityType.hpp"
#include "../components/Health.hpp"
#include "../components/Laser.hpp"
#include "../components/Motion.hpp"
#include "../components/Position.hpp"

namespace Systems
{

auto movement_system(
    Registry &r,
    std::unordered_map<std::size_t, std::tuple<Position, Motion, EntityTag>>
        items) -> void;
// bullets collision between boss and players
auto collision_system(
    Registry &r,
    std::unordered_map<std::size_t, std::tuple<Collision, EntityTag>> items)
    -> void;

// just remove boss bullets when not on screen anymore
auto cleanup_system(
    Registry &r,
    std::unordered_map<std::size_t, std::tuple<Position, EntityTag>> items)
    -> void;
} // namespace Systems

#endif /* COMP_POSITION_HPP */
