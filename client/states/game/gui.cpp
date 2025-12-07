/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** in game state gui
*/

#include "gui.hpp"

#include "systems/Systems.hpp"

InGameStateGui::InGameStateGui(Registry &r)
{
    r.add_render_system<Position, Square>(renderSquare);
}

auto InGameStateGui::render(Registry &r) -> void
{
    r.render();
}
