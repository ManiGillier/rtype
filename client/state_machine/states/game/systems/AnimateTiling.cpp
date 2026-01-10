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
    TextureManager &manager)
-> void
{
    for (auto &&[_, tiling, texture] : zip) {
        tiling->horizontal_pos += tiling->speed * raylib::GetFrameTime();
        float width = 
            (float) manager.getTexture(texture->texture_path).getWidth()
            *
            (
               (float) raylib::GetRenderHeight()
               /
               (float) manager.getTexture(texture->texture_path).getHeight()
            );
        while (tiling->horizontal_pos < -width)
            tiling->horizontal_pos += width;
        while (tiling->horizontal_pos > 0)
            tiling->horizontal_pos -= width;
    }
}
