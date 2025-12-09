/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** in game state gui
*/

#include "gui.hpp"

#include "systems/Systems.hpp"

InGameStateGui::InGameStateGui(IGameState &gm) : gameState(gm)
{
    Registry r = gameState.getRegistry();

    r.add_render_system<Position, Square>(renderSquare);
}

auto InGameStateGui::render(Registry &r) -> void
{
    r.render();
}
