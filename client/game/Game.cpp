/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** game
*/

#include "Game.hpp"
#include <thread>

Game::Game(Registry &r) : registry(r)
{
    this->gameThread = std::thread(&Game::init, this);
}

Game::~Game()
{
    this->shouldLoop = false;
    if (this->gameThread.joinable())
        this->gameThread.join();
}

#include "client/components/Square.hpp"
#include "client/components/Position.hpp"

auto Game::init() -> void
{
    Entity a = this->registry.spawn_entity();
    this->registry.add_component<Position>(a, {50, 50});
    this->registry.add_component<Square>(a, {50});
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
    this->registry.update();
}
