/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** game
*/

#ifndef GAME_HPP
#define GAME_HPP

#include "client/GameInterface.hpp"

#include "client/api/IGameState.hpp"

#include "ecs/regisrty/Registry.hpp"

#include <thread>

class Game : public GameLogicAPI
{
public:
    Game(IGameState *);
    ~Game();
private:
    auto init() -> void;
    auto loop() -> void;
    auto update() -> void;
    inline auto updateGameState(IGameState *s) -> void { this->gameState = s; }
    inline auto join() -> void { this->gameThread.join(); }
private:
    bool shouldLoop = true;
    std::thread gameThread;
    IGameState *gameState = nullptr;
};

#endif /* GAME_HPP */
