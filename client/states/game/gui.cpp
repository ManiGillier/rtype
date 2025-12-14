/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** in game state gui
*/

#include "gui.hpp"

#include "systems/Systems.hpp"

#include <raylib.h>

InGameStateGui::InGameStateGui(IGameState &gm) : gameState(gm)
{
    Registry &r = gameState.getRegistry();

    r.add_render_system<Position, HitBox, ElementColor>(renderSquare);
}

auto InGameStateGui::render(Registry &r) -> void
{
    r.render();
}
