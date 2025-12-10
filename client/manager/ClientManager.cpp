/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** client manager
*/

#include "ClientManager.hpp"
#include "client/game/Game.hpp"
#include "client/raylib/Raylib.hpp"

#include <memory>

ClientManager::ClientManager()
{
    this->registerComponents();
    this->registerSystems();
    this->game = std::make_unique<Game>(this->registry);
    this->gui = std::make_unique<Raylib>(this->registry);
}

ClientManager::~ClientManager() {}

#include "client/components/Position.hpp"
#include "client/components/Square.hpp"

auto ClientManager::registerComponents() -> void
{
    this->registry.register_component<Position>();
    this->registry.register_component<Square>();
}

#include "client/raylib/systems/Systems.hpp"

auto ClientManager::registerSystems() -> void
{
    //this->registry.add_render_system<Position, Square>(renderSquare);
}
