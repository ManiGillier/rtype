/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** JoinOrCreatePublicLobbyExecutor
*/

#ifndef JOIN_OR_CREATE_PUB_EXEC_HPP_
#define JOIN_OR_CREATE_PUB_EXEC_HPP_

#include "../../player/Player.hpp"
#include <memory>
#include "network/packets/impl/JoinOrCreatePublicLobby.hpp"
#include <network/server/Server.hpp>

class RTypeServer;

class JoinOrCreatePublicLobbyExecutor
    : public PacketExecutorImplServer<JoinOrCreatePublicLobbyPacket, Player>
{
  public:
    JoinOrCreatePublicLobbyExecutor(RTypeServer &server);
    ~JoinOrCreatePublicLobbyExecutor() = default;
    bool execute(
        Server &server, std::shared_ptr<Player> player,
        std::shared_ptr<JoinOrCreatePublicLobbyPacket> packet);
    int getPacketId() const
    {
        return PacketId::JOIN_OR_CREATE_PUBLIC_LOBBY_PACKET;
    }

  private:
    RTypeServer &_rtypeServer;
};
#endif /* !JOIN_OR_CREATE_PUB_EXEC_HPP_ */
