/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** game player list state system
*/

#include <graphical_library/api/GraphicalLibrary.hpp>

#include <ecs/regisrty/Registry.hpp>

#include "../Game.hpp"

auto lobbyPlayerList([[maybe_unused]] Registry &r,
                     gl::GraphicalLibrary &gl,
                     Game &game)
-> void
{
    int height = 100;

    for (auto &player : game.getPlayerList()) {
        const int fontSize = 40;
        const int width = gl.getTextWidth(player.first, fontSize);
        const gl::Text text = {
            player.first,
            {
                (int) gl.get_window_size().x - width - 20,
                height
            },
            fontSize,
            player.second ? gl::WHITE : gl::RED};

        gl.draw(text);

        height += fontSize + fontSize / 2;
    }
}
