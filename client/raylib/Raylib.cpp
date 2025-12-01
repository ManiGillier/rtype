/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/

#include <raylib.h>
#include <thread>


#include "Raylib.hpp"

Raylib::Raylib()
{
    this->openGlThread = std::thread(&Raylib::init, this);
}

Raylib::~Raylib()
{
    if (this->openGlThread.joinable())
        this->openGlThread.join();
}

auto Raylib::init() -> void
{
#if LOG_LEVEL_DEBUG
    SetTraceLogLevel(LOG_DEBUG);
#else
    SetTraceLogLevel(LOG_NONE);
#endif /* DEBUG */

    InitWindow(this->window.getWidth(),
               this->window.getHeight(),
               this->window.getTitle());

    this->loop();
}

auto Raylib::loop() -> void
{
    while (!WindowShouldClose())
        this->update();
}

auto Raylib::update() -> void {}
