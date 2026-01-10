/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** connecting state system
*/

#include <graphical_library/api/GraphicalLibrary.hpp>
#include <graphical_library/raylib/text/Text.hpp>

#include <ecs/regisrty/Registry.hpp>

namespace raylib {
    #include <raylib.h>
}

auto connectingText([[maybe_unused]] Registry &r, gl::GraphicalLibrary &gl)
-> void
{
    (void) gl;
    const char *txt = "Authentification... Please wait!";
    const int fontSize = 40;
    Text text(txt);
    const int width = text.size(fontSize);

    text.draw(gl::WorldPosition {
        (float) raylib::GetRenderWidth() / 2 - (float) width / 2,
        (float) 50
    }, fontSize, gl::WHITE);
}
