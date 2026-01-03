/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** state machine
*/

#ifndef CLIENT_STATE_MACHINE_HPP
#define CLIENT_STATE_MACHINE_HPP

#include "IState.hpp"
#include <memory>

class StateMachine {
public:
    StateMachine(std::unique_ptr<IState>);

    auto switch_state(std::unique_ptr<IState>) -> void;
    auto operator*() -> IState &;
    auto operator->() -> IState *;
private:
    std::unique_ptr<IState> current_state;
};

#endif /* CLIENT_STATE_MACHINE_HPP */
