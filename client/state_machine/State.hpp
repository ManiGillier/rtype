/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** state machine state
*/

#ifndef CLIENT_ABSTRACT_STATE_HPP
#define CLIENT_ABSTRACT_STATE_HPP

#include "IState.hpp"
#include "client/manager/ClientManager.hpp"

#include <ecs/regisrty/Registry.hpp>
#include <memory>


class State : public IState {
public:
    State(ClientManager &, Registry&);
    virtual ~State() = default;

    inline auto getRegistry() -> Registry & { return this->registry; }
    auto getGraphicalLibrary() -> gl::GraphicalLibrary &;

    auto update() -> std::unique_ptr<IState>;
protected:
    auto change_state(std::unique_ptr<IState>) -> void;
    ClientManager &clientManager;
    Registry &registry;
private:
    std::unique_ptr<IState> next_state = nullptr;
};

#endif /* CLIENT_ABSTRACT_STATE_HPP */
