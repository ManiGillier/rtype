/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** lobby player list state system
*/

#include <graphical_library/api/GraphicalLibrary.hpp>

#include <ecs/regisrty/Registry.hpp>

#include "../Lobby.hpp"

auto lobbyPlayerList([[maybe_unused]] Registry &r,
                     gl::GraphicalLibrary &gl,
                     Lobby &lobby)
-> void
{
    int height = 20;

    for (auto &player : lobby.getPlayerList()) {
        const int fontSize = 40;
        const int width = gl.getTextWidth(player, fontSize);
        const gl::Text text = {
            player,
            {
                (int) gl.get_window_size().x - width - 20,
                height
            },
            fontSize,
            gl::WHITE};

        gl.draw(text);

        height += fontSize + fontSize / 2;
    }
}
