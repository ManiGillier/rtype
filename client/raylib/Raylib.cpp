/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/

#include <raylib.h>
#include <thread>


#include "Raylib.hpp"

Raylib::Raylib(Registry &reg) : registry(reg)
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
    SetTraceLogLevel(RAYLIB_LOG_LEVEL);
    InitWindow(this->window.getWidth(),
               this->window.getHeight(),
               this->window.getTitle());
    SetTargetFPS(this->window.getFps());

    this->loop();

    CloseWindow();
}

auto Raylib::loop() -> void
{
    while (!WindowShouldClose())
        this->update();
}

auto Raylib::update() -> void
{
    BeginDrawing();
    ClearBackground(BLACK);
    DrawRectangle(10, 10, 10, 10, WHITE);
    DrawRectangle(0, 10, 10, 10, WHITE);
    DrawRectangle(10, 0, 10, 10, WHITE);
    EndDrawing();
}
