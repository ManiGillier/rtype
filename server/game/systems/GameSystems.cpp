#include "GameSystems.hpp"
#include "ecs/sparse_array/SparseArray.hpp"
#include "network/packets/impl/DespawnPlayerPacket.hpp"
#include "network/packets/impl/LaserActiveUpdatePacket.hpp"
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
#include "../Game.hpp"

namespace GameConstants
{
constexpr float width = 800;
constexpr float height = 600;
constexpr float PLAYER_SPEED = 5.0f;
} // namespace GameConstants

auto Systems::position_system(
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
        game.sendPackets(
            std::make_shared<PositionUpdatePacket>(i, pos->x, pos->y));
    }
}

auto Systems::player_velocity_system(Registry &r,
                          std::shared_ptr<ClientInputsPacket> packet,
                          std::size_t id) -> void
{
    auto &positions = r.get_components<Position>();
    auto &velocities = r.get_components<Velocity>();
    // auto &dependences = r.get_components<Dependence>();
    // auto &lasers = r.get_components<Laser>();

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
}
