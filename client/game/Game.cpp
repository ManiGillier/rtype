/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** game
*/

#include "Game.hpp"
#include <thread>
#include <unistd.h>

Game::Game(IGameState *gameState) : gameState(gameState)
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
}

auto Game::update() -> void
{
    if (this->gameState)
        this->gameState->update();
}
