#include "./ClientInputsExecutor.hpp"
#include "../RTypeServer.hpp"
#include "../systems/GameSystems.hpp"
#include "network/packets/impl/PositionUpdatePacket.hpp"
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

    return true;
}

int ClientInputsExecutor::getPacketId() const
{
    return PacketId::CLIENT_INPUTS;
}
