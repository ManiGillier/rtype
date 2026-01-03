/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** state machine state
*/

#ifndef CLIENT_ABSTRACT_STATE_HPP
#define CLIENT_ABSTRACT_STATE_HPP

#include "IState.hpp"

#include <ecs/regisrty/Registry.hpp>
#include <memory>

class State : public IState {
public:
    State(Registry&);

    auto update() -> std::unique_ptr<IState>;
protected:
    auto change_state(std::unique_ptr<IState>) -> void;
    Registry &registry;
private:
    std::unique_ptr<IState> next_state = nullptr;
};

#endif /* CLIENT_ABSTRACT_STATE_HPP */
