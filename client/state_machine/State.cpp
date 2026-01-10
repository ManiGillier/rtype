/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** state machine state
*/

#include "State.hpp"
#include <memory>

State::State(ClientManager &cm, Registry &registry)
    : clientManager(cm), registry(registry)
{}

auto State::update() -> std::unique_ptr<IState>
{
    this->registry.update();
    this->registry.render();
    return std::move(this->next_state);
}

auto State::getGraphicalLibrary() -> gl::GraphicalLibrary &
{
    return this->clientManager.getGui();
}
