/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** animate tiling system
*/

#include "Systems.hpp"

auto animateTiling([[maybe_unused]] Registry &r,
    containers::indexed_zipper<SparseArray<HorizontalTiling>,
                               SparseArray<TextureComp>> zip,
    gl::GraphicalLibrary &gl)
-> void
{
    for (auto &&[_, tiling, texture] : zip) {
        tiling->horizontal_pos += tiling->speed * gl.getDeltaTime();
        float width =
            (float) gl.getTexture(texture->texture_name).size.x
            *
            (
               (float) gl.get_window_size().y
               /
               (float) gl.getTexture(texture->texture_name).size.y
            );
        while (tiling->horizontal_pos < -width)
            tiling->horizontal_pos += width;
        while (tiling->horizontal_pos > 0)
            tiling->horizontal_pos -= width;
    }
}
