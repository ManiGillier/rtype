/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** lobby state gui
*/

#include "gui.hpp"

LobbyStateGui::LobbyStateGui(IGameState &gs) : gameState(gs)
{
}

auto LobbyStateGui::render(Registry &r) -> void
{
    r.render();
}
