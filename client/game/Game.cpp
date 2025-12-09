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

Game::Game(IGameState *gameState, CommandManager &cm)
    : commandManager(cm), gameState(gameState)
{
    this->gameThread = std::thread(&Game::init, this);
}

Game::~Game()
{
    this->shouldLoop = false;
    if (this->gameThread.joinable())
        this->gameThread.join();
}

auto Game::init() -> void
{
    this->loop();
}

auto Game::loop() -> void
{
    while (this->shouldLoop) {
        this->update();
    }
    this->commandManager.sendCommandToRender<StopCommand>();
}

auto Game::update() -> void
{
    if (this->gameState)
        this->gameState->update();
}
