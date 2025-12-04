/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** game logic interface
*/

#ifndef GAME_LOGIC_INTERFACE_HPP
#define GAME_LOGIC_INTERFACE_HPP

#include "ecs/regisrty/Registry.hpp"

class ILogic {
public:
    virtual auto update(Registry &) -> void;
};

#endif /* GAME_LOGIC_INTERFACE_HPP */
