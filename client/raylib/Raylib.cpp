/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/

#include <raylib.h>
#include <thread>

#include "client/commands/Stop.hpp"

#include "Raylib.hpp"

Raylib::Raylib(ClientManager &cm)
    : clientManager(cm)
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
    while (!WindowShouldClose() && !this->shouldStop)
        this->update();
    this->clientManager.getCommandManager().sendCommandToLogic<StopCommand>();
}

auto Raylib::update() -> void
{
    this->manageCommands();
    if (this->shouldStop)
        return;
    BeginDrawing();
    ClearBackground(BLACK);
    this->clientManager.getState().render();
    EndDrawing();
}

auto Raylib::stop() -> void
{
    this->shouldStop = true;
}

auto Raylib::manageCommand(Command &c) -> void
{
    switch (c.getId()) {
        case Command::STOP:
            this->stop();
            break;
    } ;
}

#include <memory>

auto Raylib::manageCommands() -> void
{
    std::queue<std::unique_ptr<Command>> commands =
        this->clientManager.getCommandManager().readRenderCommands();

    while (!commands.empty()) {
        std::unique_ptr<Command> command = std::move(commands.front());
        commands.pop();
        this->manageCommand(*command);
    }
}
