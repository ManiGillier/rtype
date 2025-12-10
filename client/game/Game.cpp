/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** game
*/

#include "Game.hpp"
#include <thread>
#include <unistd.h>

#include "client/commands/Stop.hpp"

Game::Game(ClientManager &cm)
    : clientManager(cm)
{
    this->gameThread = std::thread(&Game::init, this);
}

Game::~Game()
{
    this->shouldStop = true;
    if (this->gameThread.joinable())
        this->gameThread.join();
}

auto Game::init() -> void
{
    this->loop();
}

auto Game::loop() -> void
{
    while (!this->shouldStop) {
        this->update();
    }
    this->clientManager.getCommandManager().sendCommandToRender<StopCommand>();
}

auto Game::update() -> void
{
    this->manageCommands();
    if (this->shouldStop)
        return;
    this->clientManager.getState().update();
}

auto Game::stop() -> void
{
    this->shouldStop = true;
}

auto Game::manageCommand(Command &c) -> void
{
    switch (c.getId()) {
        case Command::STOP:
            this->stop();
            break;
    } ;
}

#include <memory>

auto Game::manageCommands() -> void
{
    std::queue<std::unique_ptr<Command>> commands =
        this->clientManager.getCommandManager().readLogicCommands();

    while (!commands.empty()) {
        std::unique_ptr<Command> command = std::move(commands.front());
        commands.pop();
        this->manageCommand(*command);
    }
}
