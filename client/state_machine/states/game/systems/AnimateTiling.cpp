/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** animate tiling system
*/

#include "Systems.hpp"
namespace raylib {
    #include <raylib.h>
}

auto animateTiling([[maybe_unused]] Registry &r,
    containers::indexed_zipper<SparseArray<HorizontalTiling>,
                               SparseArray<TextureComp>> zip,
    gl::GraphicalLibrary &gl)
-> void
{
    for (auto &&[_, tiling, texture] : zip) {
        tiling->horizontal_pos += tiling->speed * raylib::GetFrameTime();
        float width =
            (float) gl.getTexture(texture->texture_path).size.x
            *
            (
               (float) raylib::GetRenderHeight()
               /
               (float) gl.getTexture(texture->texture_path).size.y
            );
        while (tiling->horizontal_pos < -width)
            tiling->horizontal_pos += width;
        while (tiling->horizontal_pos > 0)
            tiling->horizontal_pos -= width;
    }
}
