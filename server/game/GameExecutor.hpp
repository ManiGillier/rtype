/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** Server
*/

#ifndef GAME_EXECUTOR_HPP
#define GAME_EXECUTOR_HPP

#include "../player/Player.hpp"
#include <network/packets/impl/GameStartPacketRequest.hpp>
#include <network/server/Server.hpp>

class GameExecutor
    : public PacketExecutorImplServer<GameStartPacketRequest, Player>
{
  public:
    GameExecutor() = default;
    ~GameExecutor() = default;
    bool execute(Server &server, std::shared_ptr<Player> &player,
                 std::shared_ptr<GameStartPacketRequest> packet);
    int getPacketId() const
    {
        return 69;
    };

  private:
    bool _hasStarted = false;
};

#endif
