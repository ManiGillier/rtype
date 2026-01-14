#include "JoinOrCreatePublicLobbyExecutor.hpp"
#include "../server/RTypeServer.hpp"
#include "network/packets/impl/JoinOrCreatePublicLobby.hpp"
#include <network/packets/impl/JoinedLobbyPacket.hpp>

JoinOrCreatePublicLobbyExecutor::JoinOrCreatePublicLobbyExecutor(RTypeServer &server)
    : _rtypeServer(server)
{
}

bool JoinOrCreatePublicLobbyExecutor::execute(
    Server &server, std::shared_ptr<Player> player,
    std::shared_ptr<JoinOrCreatePublicLobbyPacket> packet)
{
    (void)server;
    (void)packet;

    this->_rtypeServer.getLobbyManager().joinPublicLobby(player);
    player->sendPacket(create_packet(JoinedLobbyPacket, player->getLobbyId()));
    return false;
}
