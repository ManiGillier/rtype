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
#include "client/manager/ClientManager.hpp"

#include "ecs/regisrty/Registry.hpp"


class Raylib : public GraphicalLibAPI {
public:
    Raylib(ClientManager &);
    ~Raylib();

    auto manageCommand(Command &) -> void;
    auto manageCommands() -> void;
private:
    auto init() -> void;
    auto loop() -> void;
    auto update() -> void;
    auto stop() -> void;
private:
    ClientManager &clientManager;
    std::thread openGlThread;
    RenderWindow window;
    bool shouldStop = false;
};

#endif // RAYLIB_H_
