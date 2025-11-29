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

class Raylib : public GraphicalLibAPI {
public:
    Raylib();
    ~Raylib();
private:
    auto init() -> void;
    auto loop() -> void;
    auto update(const Registry &) -> void;
private:
    std::thread openGlThread;
    RenderWindow window;
};

#endif // RAYLIB_H_
