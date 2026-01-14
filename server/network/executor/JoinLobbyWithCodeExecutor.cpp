#include "JoinLobbyWithCodeExecutor.hpp"
#include "../server/RTypeServer.hpp"
#include <network/packets/impl/JoinedLobbyPacket.hpp>

JoinLobbyWithCodeExecutor::JoinLobbyWithCodeExecutor(RTypeServer &server)
    : _rtypeServer(server)
{
}

bool JoinLobbyWithCodeExecutor::execute(
    Server &server, std::shared_ptr<Player> player,
    std::shared_ptr<JoinLobbyWithCodePacket> packet)
{
    (void)server;
    (void)packet;

    this->_rtypeServer.getLobbyManager().joinLobby(packet->getCode(), player);
    player->sendPacket(create_packet(JoinedLobbyPacket, player->getLobbyId()));
    return true;
}
