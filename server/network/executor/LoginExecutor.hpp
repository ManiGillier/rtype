/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** LoginExecutor
*/

#ifndef LOGINEXECUTOR_HPP_
    #define LOGINEXECUTOR_HPP_

#include "../../player/Player.hpp"
#include <network/packets/PacketManager.hpp>
#include <network/packets/impl/LoginPacket.hpp>
#include <network/server/Server.hpp>
#include <memory>

#define LOG_EMPTY_USERNAME_OR_PASSWORD "tried to login with empty username or password, disconnecting.."

class RTypeServer;

class LoginExecutor
    : public PacketExecutorImplServer<LoginPacket, Player>
{
  public:
    LoginExecutor(RTypeServer &server);
    ~LoginExecutor() = default;
    bool execute(Server &server, std::shared_ptr<Player> player,
                 std::shared_ptr<LoginPacket> packet);
    int getPacketId() const {
        return PacketId::LOGIN_PACKET;
    }

  private:
    RTypeServer &_rtypeServer;
};
#endif /* !LOGINEXECUTOR_HPP_ */
