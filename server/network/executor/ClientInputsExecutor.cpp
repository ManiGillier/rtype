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
    (void)player;
    (void)packet;
    // auto &game = _rtypeServer.getGame();
    // auto &registry = game.getRegistry();
    // auto &mutex = game.getRegistryMutex();
    // std::size_t player_id = player->getId();
    //
    // LOG("Client inputs update");
    // {
    //     std::lock_guard<std::mutex> lock(mutex);
    //     Systems::update_player_system(registry, packet, player_id);
    // }
    return true;
}

int ClientInputsExecutor::getPacketId() const
{
    return PacketId::CLIENT_INPUTS;
}
