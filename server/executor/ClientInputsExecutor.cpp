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
    (void)server;
    auto &game = _rtypeServer.getGame();
    auto &registry = game.getRegistry();
    auto &mutex = game.getRegistryMutex();
    std::size_t player_id = player->getId();

    LOG("Client inputs update");
    {
        std::lock_guard<std::mutex> lock(mutex);
        Systems::update_player_system(registry, packet, player_id);
    }
    return true;
}

int ClientInputsExecutor::getPacketId() const
{
    return PacketId::CLIENT_INPUTS;
}
