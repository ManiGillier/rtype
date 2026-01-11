/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** laser sound system
*/

#include "ecs/regisrty/Registry.hpp"

#include <graphical_library/api/GraphicalLibrary.hpp>

#include <raylib.h>

auto laserSound([[maybe_unused]] Registry &r, gl::GraphicalLibrary &gl)
-> void
{
    if (IsKeyPressed(KEY_SPACE)) {
        gl.play(gl.getSound("laser"));
    }
}
