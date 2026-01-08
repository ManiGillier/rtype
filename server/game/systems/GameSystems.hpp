/*
 ** EPITECH PROJECT, 2025
 ** rtype
 ** File description:
 ** position component
 */

#ifndef COMP_POSITION_HPP
#define COMP_POSITION_HPP

#include "../../network/network_manager/NetworkManager.hpp"
#include "../components/Acceleration.hpp"
#include "../components/Damager.hpp"
#include "../components/OutsideBoundaries.hpp"
#include "../components/Resistance.hpp"
#include "../components/Velocity.hpp"
#include "ecs/regisrty/Registry.hpp"
#include "ecs/sparse_array/SparseArray.hpp"
#include "shared/components/Dependence.hpp"
#include "shared/components/Health.hpp"
#include "shared/components/HitBox.hpp"
#include "shared/components/Laser.hpp"
#include "shared/components/Position.hpp"
#include <network/packets/PacketManager.hpp>
#include <network/packets/impl/ClientInputsPacket.hpp>

namespace Systems
{
auto position_system(
    Registry &r,
    containers::indexed_zipper<SparseArray<Position>, SparseArray<Velocity>,
                               SparseArray<Acceleration>,
                               SparseArray<OutsideBoundaries>>
        zipper,
    NetworkManager &nm) -> void;

auto update_laser_system(
    Registry &r,
    containers::indexed_zipper<SparseArray<Position>, SparseArray<Laser>>
        zipper,
    NetworkManager &nm) -> void;

auto player_velocity_system(Registry &r,
                            std::shared_ptr<ClientInputsPacket> packet,
                            std::size_t id) -> void;
auto player_laser_system(Registry &r,
                         std::shared_ptr<ClientInputsPacket> packet,
                         std::size_t id) -> void;
} // namespace Systems

#endif /* COMP_POSITION_HPP */
