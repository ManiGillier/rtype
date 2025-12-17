/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** Server
*/

#ifndef RTYPES_SERVER_HPP_
#define RTYPES_SERVER_HPP_

#include "game/Game.hpp"
#include <atomic>
#include <memory>
#include <network/server/Server.hpp>

class RTypeServer : public Server
{
  public:
    RTypeServer(int port, int ticks);
    ~RTypeServer() = default;
    std::shared_ptr<IPollable> createClient(int fd) override;
    void onClientConnect(std::shared_ptr<IPollable> client) override;
    void onClientDisconnect(std::shared_ptr<IPollable> client) override;

    Game &getGame();
    int getTicks() const;
    void setStart();
    bool canStart() const;
    bool getRunning() const;
    void setRunning(bool r);

private:
    [[maybe_unused]] std::size_t _next_id;
    int _ticks;
    bool _canStartGame;
    std::atomic<bool> _isRunning;
    Game _game;
};

#endif
