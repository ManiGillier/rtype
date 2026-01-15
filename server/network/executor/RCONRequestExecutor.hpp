/*
** EPITECH PROJECT, 2026
** rtype [WSL: Ubuntu-24.04]
** File description:
** RCONRequestExecutor
*/

#ifndef RCONREQUESTEXECUTOR_HPP_
#define RCONREQUESTEXECUTOR_HPP_

#include "../../player/Player.hpp"
#include <network/packets/PacketManager.hpp>
#include <network/packets/impl/RCONRequest.hpp>
#include <network/server/Server.hpp>
#include <memory>

class RTypeServer;

class RCONRequestExecutor
    : public PacketExecutorImplServer<RCONRequest, Player>
{
  public:
    RCONRequestExecutor(RTypeServer &server);
    ~RCONRequestExecutor() = default;
    bool execute(Server &server, std::shared_ptr<Player> player,
                 std::shared_ptr<RCONRequest> packet);
    int getPacketId() const {
        return PacketId::RCON_REQUEST;
    }

  private:
    void kick(std::shared_ptr<Player> player, const std::string &target);
    void ban(std::shared_ptr<Player> player, const std::string &target);
    void list(std::shared_ptr<Player> player);
    RTypeServer &_rtypeServer;
};

#endif /* !RCONREQUESTEXECUTOR_HPP_ */
