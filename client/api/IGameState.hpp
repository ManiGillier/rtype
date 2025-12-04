/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** game state interface
*/

#ifndef GAME_STATE_INTERFACE_HPP
#define GAME_STATE_INTERFACE_HPP

#include "ecs/regisrty/Registry.hpp"

class IGameState {
public:
    virtual auto getRegistry() -> Registry& = 0;
    virtual auto render() -> void = 0;
    virtual auto update() -> void = 0;
};

#endif /* GAME_STATE_INTERFACE_HPP */
