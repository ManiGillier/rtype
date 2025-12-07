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

#include "systems/Systems.hpp"

InGameState::InGameState()
{
    this->reg.register_component<Position>();
    this->reg.register_component<Square>();
    this->reg.register_component<PlayerControler>();

    this->gui = std::make_unique<InGameStateGui>(this->reg);
    this->logic = std::make_unique<InGameStateLogic>(this->reg);
}
