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

class IGameState {
public:
    inline auto getRegistry() -> Registry & { return this->reg; }
    inline auto render() -> void { this->gui->render(this->getRegistry()); }
    inline auto update() -> void { this->logic->update(this->getRegistry()); }
protected:
    Registry reg;
    std::unique_ptr<GUI> gui = nullptr;
    std::unique_ptr<ILogic> logic = nullptr;
};

#endif /* GAME_STATE_INTERFACE_HPP */
