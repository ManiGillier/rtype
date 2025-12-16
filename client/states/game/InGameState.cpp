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
#include "shared/components/Dependence.hpp"
#include "shared/components/Health.hpp"
#include "shared/components/Laser.hpp"
#include "client/components/PlayerId.hpp"

InGameState::InGameState(ClientManager &cm) : clientManager(cm)
{
    this->reg.register_component<Position>();
    this->reg.register_component<HitBox>();
    this->reg.register_component<ElementColor>();
    this->reg.register_component<Health>();
    this->reg.register_component<Dependence>();
    this->reg.register_component<Laser>();
    this->reg.register_component<HorizontalTiling>();
    this->reg.register_component<TextureComp>();
    this->reg.register_component<PlayerId>();

    std::unique_ptr<InGameStateLogic> l = std::make_unique<InGameStateLogic>
        (*this, this->clientManager.getNetworkManager());
    this->gui = std::make_unique<InGameStateGui>
                    (*this, this->clientManager.getNetworkManager(),
                     std::ref(*l));
    this->logic = std::move(l);
}

auto InGameState::update() -> State
{
    if (this->logic)
        return this->logic->update(this->getRegistry());
    return State::NONE;
}

auto InGameState::render() -> void
{
    if (this->gui)
        this->gui->render(this->getRegistry());
}
