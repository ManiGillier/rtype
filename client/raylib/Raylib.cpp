/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/

#include <thread>
#include <raylib.h>

#include "Raylib.hpp"

Raylib::Raylib(ClientManager &cm)
    : clientManager(cm)
{
    SetTraceLogLevel(RAYLIB_LOG_LEVEL);
    InitWindow(this->window.getWidth(),
               this->window.getHeight(),
               this->window.getTitle());
    SetTargetFPS(this->window.getFps());
}

Raylib::~Raylib()
{
    this->stopped = true;
    CloseWindow();
}

auto Raylib::isStopped() -> bool
{
    return WindowShouldClose() || this->stopped;
}

auto Raylib::render(IGameState &gs) -> void
{
    BeginDrawing();
    ClearBackground(BLACK);
    gs.render();
    EndDrawing();
}
