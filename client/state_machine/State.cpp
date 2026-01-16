/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** state machine state
*/

#include "State.hpp"
#include <memory>

State::State(ClientManager &cm, Registry &registry, Sync &s)
    : clientManager(cm), registry(registry), sync(s)
{}

auto State::update() -> std::unique_ptr<IState>
{
    if (this->guiScene) {
        this->guiScene->update();
        this->guiScene->draw();
    }
    this->registry.update();
    this->registry.render();
    return std::move(this->next_state);
}

auto State::getGraphicalLibrary() -> gl::GraphicalLibrary &
{
    return this->clientManager.getGui();
}
