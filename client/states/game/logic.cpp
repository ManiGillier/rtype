/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** in game state logic
*/

#include "logic.hpp"

#include "shared/components/Position.hpp"

#include "client/components/Color.hpp"

#include "systems/Systems.hpp"

#include <iostream>
#include <cstddef>
#include <cstdint>

InGameStateLogic::InGameStateLogic(IGameState &gs)
    : gameState(gs), player(gameState.getRegistry().spawn_entity())
{
    Registry &r = gameState.getRegistry();

    r.add_component<Position>(this->player, {20, 20});
    r.add_component<HitBox>(this->player, {20, 20});
    r.add_component<SquareColor>(this->player, {WHITE});
}

auto InGameStateLogic::update(Registry &r) -> void
{
    r.update();
}
