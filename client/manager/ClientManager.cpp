/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** client manager
*/

#include "ClientManager.hpp"
#include "client/raylib/Raylib.hpp"

#include "client/states/game/InGameState.hpp"

#include <memory>

ClientManager::ClientManager()
{
    this->gui = std::make_unique<Raylib>(*this);

    this->_gameStateFactory[IN_GAME] = [this] {
        return std::make_unique<InGameState>(*this);
    };
}

auto ClientManager::changeInternalState(std::unique_ptr<IGameState> state)
-> void
{
    this->_internal_state = std::move(state);
}

auto ClientManager::changeState(const State state) -> void
{
    if (this->_state == state)
        return;
    this->changeInternalState(this->_gameStateFactory[state]());
    this->_state = state;
}

auto ClientManager::launch() -> void
{
    this->changeState(IN_GAME);
    this->loop();
}

auto ClientManager::loop() -> void
{
    while (true) {
        this->getGui().render(this->getState());
        if (this->getGui().isStopped())
            break;
        State new_state = this->getState().update();

        if (new_state == State::END_STATE)
            break;
        if (new_state != State::NONE)
            this->changeState(new_state);
    }
    this->unload();
}

auto ClientManager::unload() -> void
{
    this->_internal_state.reset();
    this->_state = END_STATE;
    this->gui.reset();
}
