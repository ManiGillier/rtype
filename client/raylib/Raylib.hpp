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

#include "client/manager/CommandManager.hpp"

class Raylib : public GraphicalLibAPI {
public:
    Raylib(IGameState *, CommandManager &);
    ~Raylib();

    auto manageCommand(Command &) -> void;
    auto manageCommands() -> void;
private:
    auto init() -> void;
    auto loop() -> void;
    auto update() -> void;
    inline auto updateGameState(IGameState *s) -> void { this->gameState = s; }
    auto stop() -> void;
private:
    CommandManager &commandManager;
    std::thread openGlThread;
    RenderWindow window;
    bool shouldStop = false;
    IGameState *gameState = nullptr;
};

#endif // RAYLIB_H_
