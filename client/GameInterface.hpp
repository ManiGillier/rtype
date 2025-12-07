/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** game logic interface
*/

#ifndef GAME_LOGIC_API_HPP
#define GAME_LOGIC_API_HPP

#include "api/IGameState.hpp"

class GameLogicAPI
{
public:
    virtual ~GameLogicAPI() = default;

    virtual auto updateGameState(IGameState *) -> void = 0;
    virtual auto join() -> void = 0;
};

#endif /* GAME_LOGIC_API_HPP */
