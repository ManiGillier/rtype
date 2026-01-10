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
#include <ecs/sync/Sync.hpp>
#include <memory>

class EndState : public IState {
public:
    auto update() -> std::unique_ptr<IState> { return nullptr; }
    auto isEnd() -> bool { return true; }
protected:
    auto change_state(std::unique_ptr<IState> s) -> void { (void) s; }
};

class State : public IState {
public:
    State(ClientManager &, Registry&, Sync &);
    virtual ~State() = default;

    inline auto getRegistry() -> Registry & { return this->registry; }
    auto getGraphicalLibrary() -> gl::GraphicalLibrary &;

    auto update() -> std::unique_ptr<IState>;
    auto isEnd() -> bool { return false; }
    template <class _State, class... Args>
    auto change_state(Args &&...) -> void;
protected:
    ClientManager &clientManager;
    Registry &registry;
    Sync &sync;
private:
    std::unique_ptr<IState> next_state = nullptr;
};

template <class _State, class... Args>
auto State::change_state(Args &&... args) -> void
{
    this->next_state = std::make_unique<_State>
        (this->clientManager, this->registry, this->sync, args...);
}


#endif /* CLIENT_ABSTRACT_STATE_HPP */
