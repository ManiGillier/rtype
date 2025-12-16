/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** connecting state
*/

#include "ConnectingState.hpp"

#include "gui.hpp"
#include "logic.hpp"

#include <memory>

ConnectingState::ConnectingState(ClientManager &cm) : clientManager(cm)
{
    this->gui = std::make_unique<ConnectingStateGui>(*this);
    this->logic = std::make_unique<ConnectingStateLogic>
                      (*this, this->clientManager.getNetworkManager());
}

auto ConnectingState::update() -> State
{
    if (this->logic)
        return this->logic->update(this->getRegistry());
    return State::NONE;
}

auto ConnectingState::render() -> void
{
    if (this->gui)
        this->gui->render(this->getRegistry());
}
