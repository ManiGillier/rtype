/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** game logic interface
*/

#ifndef GAME_LOGIC_INTERFACE_HPP
#define GAME_LOGIC_INTERFACE_HPP

#include "ecs/regisrty/Registry.hpp"
#include "client/states/State.hpp"

class ILogic {
public:
    virtual ~ILogic() = default;

    virtual auto update(Registry &) -> State = 0;
};

#endif /* GAME_LOGIC_INTERFACE_HPP */
