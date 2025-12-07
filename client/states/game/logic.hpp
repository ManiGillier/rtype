/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** in game state logic
*/

#ifndef IN_GAME_STATE_LOGIC_HPP
#define IN_GAME_STATE_LOGIC_HPP

#include "client/api/ILogic.hpp"

class InGameStateLogic : public ILogic
{
public:
    auto update(Registry &) -> void;
};

#endif /* IN_GAME_STATE_LOGIC_HPP */
