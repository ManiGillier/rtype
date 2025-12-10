/*
 ** EPITECH PROJECT, 2025
 ** rtype
 ** File description:
 ** position component
 */

#ifndef COMP_POSITION_HPP
#define COMP_POSITION_HPP

#include "../../ecs/regisrty/Registry.hpp"
#include "../../shared/components/Dependence.hpp"
#include "../../shared/components/Health.hpp"
#include "../../shared/components/HitBox.hpp"
#include "../../shared/components/Laser.hpp"
#include "../../shared/components/Position.hpp"
#include "../components/Acceleration.hpp"
#include "../components/Damager.hpp"
#include "../components/Resistance.hpp"
#include "../components/Velocity.hpp"

namespace Systems
{

auto movement_system(Registry &r) -> void;
// bullets collision between boss and players
auto collision_system(Registry &r) -> void;

// just remove boss bullets when not on screen anymore
auto cleanup_system(Registry &r) -> void;
} // namespace Systems

#endif /* COMP_POSITION_HPP */
