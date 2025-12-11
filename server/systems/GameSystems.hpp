/*
 ** EPITECH PROJECT, 2025
 ** rtype
 ** File description:
 ** position component
 */

#ifndef COMP_POSITION_HPP
#define COMP_POSITION_HPP

#include "../../ecs/regisrty/Registry.hpp"
#include "../../ecs/sparse_array/SparseArray.hpp"
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
auto movement_system(
    Registry &r,
    containers::indexed_zipper<SparseArray<Position>, SparseArray<Velocity>,
                               SparseArray<Acceleration>>
        zipper,
    int i) -> void;

auto dependence_system(
    Registry &r,
    containers::indexed_zipper<SparseArray<Position>, SparseArray<Dependence>,
                               SparseArray<Laser>>
        zipper,
    int i) -> void;

auto collision_system(
    Registry &r,
    containers::indexed_zipper<SparseArray<Position>, SparseArray<HitBox>>
        zipper,
    int i) -> void;

auto cleanup_system(Registry &r,
                    containers::indexed_zipper<SparseArray<Health>> zipper,
                    int i) -> void;
} // namespace Systems

#endif /* COMP_POSITION_HPP */
