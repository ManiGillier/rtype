#include "GameSystems.hpp"
#include "../Game.hpp"
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

namespace GameConstants
{
constexpr float width = 800;
constexpr float height = 600;
constexpr float PLAYER_SPEED = 5.0f;
} // namespace GameConstants

auto Systems::position_system(
    Registry &r,
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
        if (!out->canGoOutside) {
            if (pos->x < 0.0f)
                pos->x = 0.0f;
            if (pos->x > GameConstants::width)
                pos->x = GameConstants::width;
            if (pos->y < 0.0f)
                pos->y = 0.0f;
            if (pos->y > GameConstants::height)
                pos->y = GameConstants::height;
        } else if (out->canGoOutside &&
                   (pos->x < 0.0f || pos->x > GameConstants::width ||
                    pos->y < 0.0f || pos->y > GameConstants::height)) {
            game.sendPackets(std::make_shared<DespawnBulletPacket>(i));
            r.kill_entity(r.entity_from_index(i));
            continue;
        }
        auto packet = std::make_shared<PositionUpdatePacket>(i, pos->x, pos->y);
        if (game.getPacketFilter().shouldSend(i, packet))
            game.sendPackets(packet);
    }
}

auto Systems::update_laser_system(
    [[maybe_unused]] Registry &r,
    containers::indexed_zipper<SparseArray<Position>, SparseArray<Laser>>
        zipper,
    Game &game) -> void
{
    for (auto &&[i, pos, laser] : zipper) {
        auto packet = create_packet(LaserActiveUpdatePacket, i, laser->active,
                                    laser->length);
        if (game.getPacketFilter().shouldSend(i, packet))
            game.sendPackets(packet);
    }
}

auto Systems::player_velocity_system(Registry &r,
                                     std::shared_ptr<ClientInputsPacket> packet,
                                     std::size_t id) -> void
{
    auto &positions = r.get_components<Position>();
    auto &velocities = r.get_components<Velocity>();

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

    Systems::player_laser_system(r, packet, id);
}

auto Systems::player_laser_system(Registry &r,
                                  std::shared_ptr<ClientInputsPacket> packet,
                                  std::size_t id) -> void
{
    auto &positions = r.get_components<Position>();
    auto &dependences = r.get_components<Dependence>();
    auto &lasers = r.get_components<Laser>();

    auto &pos = positions[id].value();
    auto inputs = packet->getInputs();

    for (std::size_t i = 0; i < dependences.size(); ++i) {
        if (dependences[i].has_value() && dependences[i].value().id == id) {
            if (i < positions.size() && positions[i].has_value()) {
                positions[i].value().x = pos.x;
                positions[i].value().y = pos.y;
            }
            if (i < lasers.size() && lasers[i].has_value()) {
                lasers[i].value().active = inputs.value.shoot;
                lasers[i].value().length = GameConstants::height - pos.y;
            }
        }
    }
}
