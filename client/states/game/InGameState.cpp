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

#include "shared/components/Dependence.hpp"
#include "shared/components/Health.hpp"
#include "shared/components/Laser.hpp"
#include "client/components/PlayerId.hpp"

InGameState::InGameState(ClientManager &cm) : clientManager(cm)
{
    std::unique_ptr<InGameStateLogic> l = std::make_unique<InGameStateLogic>
        (*this, this->clientManager.getNetworkManager());
    this->gui = std::make_unique<InGameStateGui>
                    (*this, this->clientManager.getNetworkManager(),
                     std::ref(*l));
    this->logic = std::move(l);
}

auto InGameState::update() -> State_old
{
    if (this->logic)
        return this->logic->update(this->getRegistry());
    return State_old::NONE;
}

auto InGameState::render() -> void
{
    if (this->gui)
        this->gui->render(this->getRegistry());
}

auto InGameState::getGraphicalLibrary() -> gl::GraphicalLibrary & {
    return this->clientManager.getGui();
}
