#include "./ClientInputsExecutor.hpp"
#include "../RTypeServer.hpp"
#include "../systems/GameSystems.hpp"
#include "network/packets/impl/LaserActiveUpdatePacket.hpp"
#include "network/packets/impl/PositionUpdatePacket.hpp"
#include "shared/components/Dependence.hpp"
#include "shared/components/Laser.hpp"
#include "shared/components/Position.hpp"
#include <mutex>

ClientInputsExecutor::ClientInputsExecutor(RTypeServer &server)
    : _rtypeServer(server)
{
}

bool ClientInputsExecutor::execute(Server &server,
                                   std::shared_ptr<Player> player,
                                   std::shared_ptr<ClientInputsPacket> packet)
{
    auto &game = _rtypeServer.getGame();
    auto &registry = game.getRegistry();
    auto &mutex = game.getRegistryMutex();

    std::size_t player_id = player->getId();
    Position updated_position;

    LOG("Client inputs exec");
    {
        std::lock_guard<std::mutex> lock(mutex);
        Systems::update_player_system(registry, packet, player_id);

        auto positions = registry.get_components<Position>();
        if (positions.size() <= player_id || !positions[player_id].has_value())
            return false;
        updated_position = positions[player_id].value();
    }

    auto position_packet =
        create_packet(PositionUpdatePacket, player_id, updated_position.x,
                      updated_position.y);

    for (auto &pollable : server.getPollManager().getPool()) {
        pollable->sendPacket(position_packet);
    }

    {
        std::lock_guard<std::mutex> lock(mutex);
        auto &dependences = registry.get_components<Dependence>();
        auto &lasers = registry.get_components<Laser>();

        for (std::size_t i = 0; i < dependences.size(); ++i) {
            if (dependences[i].has_value() &&
                dependences[i].value().id == player_id &&
                i < lasers.size() && lasers[i].has_value()) {

                auto laser_packet = create_packet(LaserActiveUpdatePacket, i,
                    lasers[i].value().active, lasers[i].value().length);

                for (auto &pollable : server.getPollManager().getPool()) {
                    pollable->sendPacket(laser_packet);
                }
            }
        }
    }
    return true;
}

int ClientInputsExecutor::getPacketId() const
{
    return PacketId::CLIENT_INPUTS;
}
