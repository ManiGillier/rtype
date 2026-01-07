/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** lobby state
*/

#include "LobbyState.hpp"

#include "gui.hpp"
#include "logic.hpp"

#include <memory>

LobbyState::LobbyState(ClientManager &cm) : clientManager(cm)
{
    this->gui = std::make_unique<LobbyStateGui>(*this);
    this->logic = std::make_unique<LobbyStateLogic>
                      (*this, this->clientManager.getNetworkManager());
}

auto LobbyState::update() -> State_old
{
    if (this->logic)
        return this->logic->update(this->getRegistry());
    return State_old::NONE;
}

auto LobbyState::render() -> void
{
    if (this->gui)
        this->gui->render(this->getRegistry());
}

auto LobbyState::getGraphicalLibrary() -> gl::GraphicalLibrary & {
    return this->clientManager.getGui();
}
