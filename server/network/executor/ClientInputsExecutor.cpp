#include "./ClientInputsExecutor.hpp"
#include "../../game/systems/GameSystems.hpp"
#include "../server/RTypeServer.hpp"
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

    auto lobby = _rtypeServer.getLobbyManager().getLobby(player->getLobbyId());
    if (!lobby) {
        LOG("Error: Lobby not found for player " << player->getId());
        return false;
    }

    auto &game = lobby->getGame();

    if (!game.isRunning() || !player->getEntityId().has_value())
        return true;

    auto [regMtx, registry] = game.getRegistry();
    LOG("Client inputs update");
    {
        std::lock_guard<std::mutex> lock(regMtx);
        Systems::player_velocity_system(registry, packet, player->getEntityId().value());
    }
    return true;
}

int ClientInputsExecutor::getPacketId() const
{
    return PacketId::CLIENT_INPUTS;
}
