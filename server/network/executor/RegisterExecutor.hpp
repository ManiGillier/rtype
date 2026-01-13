/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** RegisterExecutor
*/

#ifndef REGISTEREXECUTOR_HPP_
    #define REGISTEREXECUTOR_HPP_

#include "../../player/Player.hpp"
#include <network/packets/PacketManager.hpp>
#include <network/packets/impl/RegisterPacket.hpp>
#include <network/server/Server.hpp>
#include <memory>

class RTypeServer;

class RegisterExecutor
    : public PacketExecutorImplServer<RegisterPacket, Player>
{
  public:
    RegisterExecutor(RTypeServer &server);
    ~RegisterExecutor() = default;
    bool execute(Server &server, std::shared_ptr<Player> player,
                 std::shared_ptr<RegisterPacket> packet);
    int getPacketId() const {
        return PacketId::REGISTER_PACKET;
    }

  private:
    RTypeServer &_rtypeServer;
};

#endif /* !REGISTEREXECUTOR_HPP_ */
