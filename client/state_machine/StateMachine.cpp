/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** state machine
*/

#include "StateMachine.hpp"
#include "IState.hpp"
#include <memory>

StateMachine::StateMachine(std::unique_ptr<IState> state)
    : current_state(std::move(state))
{}

auto StateMachine::switch_state(std::unique_ptr<IState> state) -> void
{
    if (!state)
        return;
    this->current_state = std::move(state);
    this->current_state->init_systems();
    this->current_state->init_entities();
}

auto StateMachine::operator*() -> IState &
{
    return *this->current_state.get();
}

auto StateMachine::operator->() -> IState *
{
    return this->current_state.get();
}
