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
    virtual ~IState() = default;

    virtual auto init_systems() -> void = 0;
    virtual auto init_entities() -> void = 0;

    /**
     * @return new state for change or nullptr
     */
    virtual auto update() -> std::unique_ptr<IState> = 0;
protected:
    virtual auto change_state(std::unique_ptr<IState>) -> void = 0;
};

#endif /* CLIENT_ISTATE_HPP */
