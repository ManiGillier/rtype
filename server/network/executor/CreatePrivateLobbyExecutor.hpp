/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** CreatePrivateLobbyExecutor
*/

#ifndef CREATE_PRIVATE_LOBBY_EXEC_HPP
    #define CREATE_PRIVATE_LOBBY_EXEC_HPP

#include "../../player/Player.hpp"
#include <network/packets/impl/CreatePrivateLobbyPacket.hpp>
#include <network/server/Server.hpp>
#include <memory>

class RTypeServer;

class CreatePrivateLobbyExecutor
    : public PacketExecutorImplServer<CreatePrivateLobbyPacket, Player>
{
  public:
    CreatePrivateLobbyExecutor(RTypeServer &server);
    ~CreatePrivateLobbyExecutor() = default;
    bool execute(Server &server, std::shared_ptr<Player> player,
                 std::shared_ptr<CreatePrivateLobbyPacket> packet);
    int getPacketId() const {
        return PacketId::CREATE_PRIVATE_LOBBY_PACKET;
    }

  private:
    RTypeServer &_rtypeServer;
};
#endif /* !CREATE_PRIVATE_LOBBY_EXEC_HPP */
