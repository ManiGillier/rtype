/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** client manager
*/

#include "ClientManager.hpp"
#include "EventManager.hpp"
#include "client/game/Game.hpp"
#include "client/raylib/Raylib.hpp"

#include "client/states/game/InGameState.hpp"

#include <memory>

ClientManager::ClientManager()
{
    this->game = std::make_unique<Game>(*this);
    this->gui = std::make_unique<Raylib>(*this);

    this->_gameStateFactory[IN_GAME] = [this] {
        return std::make_unique<InGameState>(*this);
    };

    this->changeState(IN_GAME);
}
ClientManager::~ClientManager()
{
    this->game->join();
    this->game.reset();
    this->gui.reset();
}

auto ClientManager::changeInternalState(std::unique_ptr<IGameState> state)
-> void
{
    this->_internal_state = std::move(state);
}

auto ClientManager::changeState(const ClientManager::State state) -> void
{
    if (this->_state == state)
        return;
    this->changeInternalState(this->_gameStateFactory[state]());
    this->_state = state;
}

auto ClientManager::getCommandManager() -> CommandManager &
{
    return this->commandManager;
}

auto ClientManager::getEventManager() -> EventManager &
{
    return this->eventManager;
}
