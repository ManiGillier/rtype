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

#include "ecs/regisrty/Registry.hpp"

class Raylib : public GraphicalLibAPI {
public:
    Raylib(Registry &);
    ~Raylib();
private:
    auto init() -> void;
    auto loop() -> void;
    auto update() -> void;
private:
    Registry &registry;
    std::thread openGlThread;
    RenderWindow window;
};

#endif // RAYLIB_H_
