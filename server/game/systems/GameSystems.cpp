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
