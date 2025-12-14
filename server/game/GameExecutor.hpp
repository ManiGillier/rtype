/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** Server
*/

#ifndef GAME_EXECUTOR_HPP
#define GAME_EXECUTOR_HPP

#include "../player/Player.hpp"
#include <network/packets/impl/StartRequestPacket.hpp>
#include <network/server/Server.hpp>
    #include <network/packets/PacketManager.hpp>
#include <thread>
#include <atomic>

class RTypeServer;

class GameExecutor
    : public PacketExecutorImplServer<StartRequestPacket, Player>
{
  public:
    GameExecutor(RTypeServer &server);
    ~GameExecutor();
    bool execute(Server &server, std::shared_ptr<Player> &player,
                 std::shared_ptr<StartRequestPacket> packet);
    int getPacketId() const
    {
        return PacketId::START_GAME;
    };
    void stop();
    void join();
    bool isRunning() const;

  private:
    void gameLoop();

    RTypeServer &_rtypeServer;
    std::atomic<bool> _hasStarted;
    std::atomic<bool> _isRunning;
    std::thread _gameThread;
};

#endif
