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
#include <thread>

class Game : public GameLogicAPI
{
public:
    Game(Registry &);
    ~Game();
private:
    auto init() -> void;
    auto loop() -> void;
    auto update() -> void;
private:
    bool shouldLoop = true;
    Registry &registry;
    std::thread gameThread;
};

#endif /* GAME_HPP */
