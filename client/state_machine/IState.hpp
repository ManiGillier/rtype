/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** state machine state
*/

#ifndef CLIENT_ISTATE_HPP
#define CLIENT_ISTATE_HPP

#include <memory>

class IState {
public:
    /**
     * @return new state for change or nullptr
     */
    virtual auto update() -> std::unique_ptr<IState>;
protected:
    virtual auto init_systems() -> void;
    virtual auto init_entities() -> void;
    virtual auto change_state(std::unique_ptr<IState>) -> void;
};

#endif /* CLIENT_ISTATE_HPP */
