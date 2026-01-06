/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** Server
*/

#ifndef CLIENT_INPUTS_HPP
#define CLIENT_INPUTS_HPP

#include "../../player/Player.hpp"
#include <network/packets/PacketManager.hpp>
#include <network/packets/impl/ClientInputsPacket.hpp>
#include <network/server/Server.hpp>
#include <memory>

class RTypeServer;

class ClientInputsExecutor
    : public PacketExecutorImplServer<ClientInputsPacket, Player>
{
  public:
    ClientInputsExecutor(RTypeServer &server);
    ~ClientInputsExecutor() = default;
    bool execute(Server &server, std::shared_ptr<Player> player,
                 std::shared_ptr<ClientInputsPacket> packet);
    int getPacketId() const;

  private:
    RTypeServer &_rtypeServer;
};

#endif
