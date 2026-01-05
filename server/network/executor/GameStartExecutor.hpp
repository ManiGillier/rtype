/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** Server
*/

#ifndef GAME_START_EXECUTOR_HPP
#define GAME_START_EXECUTOR_HPP

#include "../../player/Player.hpp"
#include <network/server/Server.hpp>
#include <network/packets/PacketManager.hpp>
#include <network/packets/impl/StartGamePacket.hpp>

class RTypeServer;

class GameStartExecutor
    : public PacketExecutorImplServer<StartGamePacket, Player>
{
  public:
    GameStartExecutor(RTypeServer &server);
    ~GameStartExecutor() = default;
    bool execute(Server &server, std::shared_ptr<Player> player,
                 std::shared_ptr<StartGamePacket> packet);
    int getPacketId() const
    {
        return PacketId::GAME_START_REQUEST;
    };

  private:
    RTypeServer &_rtypeServer;
    bool _hasStarted;
};

#endif
