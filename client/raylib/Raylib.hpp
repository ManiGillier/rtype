/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/

#ifndef RAYLIB_H_
#define RAYLIB_H_

#include <thread>

#include "client/GraphicalLibInterface.hpp"
#include "client/window/RenderWindow.hpp"

#include "client/api/IGameState.hpp"

#include "ecs/regisrty/Registry.hpp"

class Raylib : public GraphicalLibAPI {
public:
    Raylib(IGameState *);
    ~Raylib();
private:
    auto init() -> void;
    auto loop() -> void;
    auto update() -> void;
    inline auto updateGameState(IGameState *s) -> void { this->gameState = s; }
private:
    std::thread openGlThread;
    RenderWindow window;
    IGameState *gameState = nullptr;
};

#endif // RAYLIB_H_
