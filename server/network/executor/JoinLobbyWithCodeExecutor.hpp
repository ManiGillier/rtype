/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** JoinLobbyWithCodeExecutor
*/

#ifndef JOIN_LOBBY_WITH_CODE_EXEC_HPP_
#define JOIN_LOBBY_WITH_CODE_EXEC_HPP_

#include "../../player/Player.hpp"
#include <memory>
#include "network/packets/impl/JoinLobbyWithCodePacket.hpp"
#include <network/server/Server.hpp>

class RTypeServer;

class JoinLobbyWithCodeExecutor
    : public PacketExecutorImplServer<JoinLobbyWithCodePacket, Player>
{
  public:
    JoinLobbyWithCodeExecutor(RTypeServer &server);
    ~JoinLobbyWithCodeExecutor() = default;
    bool execute(
        Server &server, std::shared_ptr<Player> player,
        std::shared_ptr<JoinLobbyWithCodePacket> packet);
    int getPacketId() const
    {
        return PacketId::JOIN_LOBBY_WITH_CODE_PACKET;
    }

  private:
    RTypeServer &_rtypeServer;
};
#endif /* !JOIN_LOBBY_WITH_CODE_EXEC_HPP_ */
