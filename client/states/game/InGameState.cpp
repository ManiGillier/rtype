/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** in game state
*/

#include "InGameState.hpp"
#include "gui.hpp"
#include "logic.hpp"

#include <memory>

#include "client/raylib/systems/Systems.hpp"

InGameState::InGameState()
{
    this->reg.register_component<Position>();
    this->reg.register_component<Square>();

    this->gui = std::make_unique<InGameStateGui>(this->reg);
    this->logic = std::make_unique<InGameStateLogic>(this->reg);
}
