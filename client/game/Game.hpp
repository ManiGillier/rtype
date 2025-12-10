/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** game
*/

#ifndef GAME_HPP
#define GAME_HPP

#include "client/GameInterface.hpp"

#include "ecs/regisrty/Registry.hpp"

#include "client/manager/ClientManager.hpp"

#include <thread>

class Game : public GameLogicAPI
{
public:
    Game(ClientManager &);
    ~Game();

    auto manageCommand(Command &) -> void;
    auto manageCommands() -> void;
private:
    auto init() -> void;
    auto loop() -> void;
    auto update() -> void;
    auto stop() -> void;
    inline auto join() -> void { this->gameThread.join(); }
private:
    ClientManager &clientManager;
    bool shouldStop = false;
    std::thread gameThread;
};

#endif /* GAME_HPP */
