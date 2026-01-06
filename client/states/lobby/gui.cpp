/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** lobby state gui
*/

#include "gui.hpp"

namespace raylib {
    #include <raylib.h>
}

#include <graphical_library/raylib/text/Text.hpp>

LobbyStateGui::LobbyStateGui(IGameState &gs) : gameState(gs)
{
}

auto LobbyStateGui::render(Registry &r) -> void
{
    const char *txt = "When ready, press <SPACE>";
    const int fontSize = 40;
    Text text(txt);
    const int width = text.size(fontSize);

    text.draw(gl::WorldPosition {
        (float) raylib::GetRenderWidth() / 2 - (float) width / 2,
        (float) 50
    }, fontSize, gl::WHITE);
    r.render();
}
