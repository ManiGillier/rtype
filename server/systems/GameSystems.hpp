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
#include <network/packets/PacketManager.hpp>
#include <network/packets/impl/ClientInputsPacket.hpp>

class Game;

namespace Systems
{
auto movement_system(
    Registry &r,
    containers::indexed_zipper<SparseArray<Position>, SparseArray<Velocity>,
                               SparseArray<Acceleration>>
        zipper,
    Game &game) -> void;

auto update_player_system(Registry &r,
                          std::shared_ptr<ClientInputsPacket> packet,
                          std::size_t id) -> void;

auto collision_system(
    Registry &r,
    containers::indexed_zipper<SparseArray<Position>, SparseArray<HitBox>>
        zipper) -> void;

auto cleanup_system(Registry &r,
                    containers::indexed_zipper<SparseArray<Health>> zipper)
    -> void;
} // namespace Systems

#endif /* COMP_POSITION_HPP */
