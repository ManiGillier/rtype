/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** menu state system
*/

#include <graphical_library/api/GraphicalLibrary.hpp>

#include <ecs/regisrty/Registry.hpp>

auto menuText([[maybe_unused]] Registry &r, gl::GraphicalLibrary &gl)
-> void
{
    const char *txt = "Connect to LOBBY with <SPACE>";
    const int fontSize = 40;
    const int width = gl.getTextWidth(txt, fontSize);
    const gl::Text text = {
        txt,
        {
            (int) gl.get_window_size().x / 2 - width / 2,
            50
        },
        fontSize,
        gl::WHITE
    };

    gl.draw(text);
}
