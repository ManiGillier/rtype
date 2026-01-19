/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** Server
*/

#ifndef LOBBY_CONFIG_EXECUTOR_HPP
#define LOBBY_CONFIG_EXECUTOR_HPP

#include "../../player/Player.hpp"
#include <network/server/Server.hpp>
#include <network/packets/PacketManager.hpp>
#include <network/packets/impl/LobbyConfigPacket.hpp>

class RTypeServer;

class LobbyConfigExecutor
    : public PacketExecutorImplServer<LobbyConfigPacket, Player>
{
  public:
    LobbyConfigExecutor(RTypeServer &server);
    ~LobbyConfigExecutor() = default;
    bool execute(Server &server, std::shared_ptr<Player> player,
                 std::shared_ptr<LobbyConfigPacket> packet);
    int getPacketId() const
    {
        return PacketId::LOBBY_CONFIG_PACKET;
    };

  private:
    RTypeServer &_rtypeServer;
};

#endif
