/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** Server
*/

#ifndef RTYPES_SERVER_HPP_
#define RTYPES_SERVER_HPP_

#include "game/Game.hpp"
#include <network/server/Server.hpp>
#include <memory>

class RTypeServer : public Server
{
public:
    RTypeServer(int port, int ticks);
    std::shared_ptr<IPollable> createClient(int fd) override;
    void onClientConnect(std::shared_ptr<IPollable> client) override;
    void onClientDisconnect(std::shared_ptr<IPollable> client) override;
    void transferPacketsToGame();

    Game& getGame();
    int getTicks() const;

private:
    int _next_id;
    int _ticks;
    Game _game;
};

#endif
