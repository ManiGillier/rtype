/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** in game state logic
*/

#ifndef IN_GAME_STATE_LOGIC_HPP
#define IN_GAME_STATE_LOGIC_HPP

#include "client/api/ILogic.hpp"
#include "client/api/IGameState.hpp"

#include <optional>

class InGameStateLogic : public ILogic
{
public:
    InGameStateLogic(IGameState &gameState);

    auto update(Registry &, EventManager &) -> void;
private:
    IGameState &gameState;
    Entity player;
};

#endif /* IN_GAME_STATE_LOGIC_HPP */
