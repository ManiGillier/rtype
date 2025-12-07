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

InGameState::InGameState()
{
    this->gui = std::make_unique<InGameStateGui>();
    this->logic = std::make_unique<InGameStateLogic>();
}
