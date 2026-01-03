/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** state machine state
*/

#include "State.hpp"
#include "IState.hpp"
#include <memory>

State::State(Registry &registry)
    : registry(registry)
{
    this->init_systems();
    this->init_entities();
}

auto State::change_state(std::unique_ptr<IState> new_state) -> void
{
    this->next_state = std::move(new_state);
}

auto State::update() -> std::unique_ptr<IState>
{
    this->registry.update();
    this->registry.render();
    return std::move(this->next_state);
}
