/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** game state interface
*/

#ifndef GAME_STATE_INTERFACE_HPP
#define GAME_STATE_INTERFACE_HPP

#include "GUI.hpp"
#include "ILogic.hpp"
#include "ecs/regisrty/Registry.hpp"
#include "client/states/State.hpp"

class IGameState {
public:
    virtual ~IGameState() = default;

    inline auto getRegistry() -> Registry & { return this->reg; }
    virtual auto render() -> void = 0;
    virtual auto update() -> State = 0;
protected:
    Registry reg;
    std::unique_ptr<GUI> gui = nullptr;
    std::unique_ptr<ILogic> logic = nullptr;
};

#endif /* GAME_STATE_INTERFACE_HPP */
