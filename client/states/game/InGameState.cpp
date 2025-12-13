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

InGameState::InGameState(ClientManager &cm) : clientManager(cm)
{
    this->reg.register_component<Position>();
    this->reg.register_component<Square>();
    this->reg.register_component<PlayerControler>();

    this->gui = std::make_unique<InGameStateGui>(*this);
    this->logic = std::make_unique<InGameStateLogic>(*this);
}

auto InGameState::update() -> State
{
    if (this->logic)
        this->logic->update(this->getRegistry());
    return State::NONE;
}

auto InGameState::render() -> void
{
    if (this->gui)
        this->gui->render(this->getRegistry());
}
