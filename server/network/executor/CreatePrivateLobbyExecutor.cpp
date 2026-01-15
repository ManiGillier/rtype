#include "CreatePrivateLobbyExecutor.hpp"
#include "../server/RTypeServer.hpp"
#include <network/packets/impl/JoinedLobbyPacket.hpp>

CreatePrivateLobbyExecutor::CreatePrivateLobbyExecutor(RTypeServer &server)
    : _rtypeServer(server)
{
}

bool CreatePrivateLobbyExecutor::execute(
    Server &server, std::shared_ptr<Player> player,
    std::shared_ptr<CreatePrivateLobbyPacket> packet)
{
    (void)server;
    (void)packet;

    this->_rtypeServer.getLobbyManager().newLobby(player);
    player->sendPacket(create_packet(JoinedLobbyPacket, player->getLobbyId()));

    auto lobby = this->_rtypeServer.getLobbyManager().getLobby(player->getLobbyId());

    if (lobby) {
        LOG("Send new usrName");
        lobby->sendNewUsrnames();
    }
    return true;
}
