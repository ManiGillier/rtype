/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** connecting state system
*/

#include <graphical_library/api/GraphicalLibrary.hpp>

#include <ecs/regisrty/Registry.hpp>

namespace raylib {
    #include <raylib.h>
}

auto connectingText([[maybe_unused]] Registry &r, gl::GraphicalLibrary &gl)
-> void
{
    const char *txt = "Authentification... Please wait!";
    const int fontSize = 40;
    const int width = gl.getTextWidth(txt, fontSize);
    const gl::Text text = {
        txt,
        {
            raylib::GetRenderWidth() / 2 - width / 2,
            50
        },
        fontSize,
        gl::WHITE
    };

    gl.draw(text);
}
