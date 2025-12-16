/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** lobby state gui
*/

#include "gui.hpp"
#include <raylib.h>

LobbyStateGui::LobbyStateGui(IGameState &gs) : gameState(gs)
{
}

auto LobbyStateGui::render(Registry &r) -> void
{
    const char *txt = "When ready, press <SPACE>";
    const int fontSize = 40;
    const int width = MeasureText(txt, fontSize);

    DrawText(txt, GetRenderWidth() / 2 - width / 2, 50, fontSize, WHITE);
    r.render();
}
