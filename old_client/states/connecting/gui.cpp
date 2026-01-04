/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** connecting state gui
*/

#include "gui.hpp"
#include <raylib.h>

ConnectingStateGui::ConnectingStateGui(IGameState &gs) : gameState(gs)
{
}

auto ConnectingStateGui::render(Registry &r) -> void
{
    const char *txt = "Authentification... Please wait!";
    const int fontSize = 40;
    const int width = MeasureText(txt, fontSize);

    DrawText(txt, GetRenderWidth() / 2 - width / 2, 50, fontSize, WHITE);
    r.render();
}
