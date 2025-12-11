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

    this->clientManager.getEventManager().resetEventListening();
    this->clientManager.getEventManager().startListenToEvent(EventId::LEFT);
    this->clientManager.getEventManager().startListenToEvent(EventId::RIGHT);
    this->clientManager.getEventManager().startListenToEvent(EventId::UP);
    this->clientManager.getEventManager().startListenToEvent(EventId::DOWN);
    this->clientManager.getEventManager().startListenToEvent(EventId::SHOOT);

    this->gui = std::make_unique<InGameStateGui>(*this);
    this->logic = std::make_unique<InGameStateLogic>(*this);
}

auto InGameState::render() -> void
{
    this->gui->manageEvents(this->clientManager.getEventManager());
    this->gui->render(this->getRegistry());
}

auto InGameState::update() -> void
{
    this->logic->update(this->getRegistry(),
                        this->clientManager.getEventManager());
}
