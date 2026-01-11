/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** render horizontally tiled texture
*/

#include "Systems.hpp"

namespace raylib {
    #include <raylib.h>
}

auto renderHTiledTexture([[maybe_unused]] Registry &r,
    containers::indexed_zipper<SparseArray<HorizontalTiling>,
                               SparseArray<TextureComp>> zip,
    gl::GraphicalLibrary &gl)
-> void
{
    for (auto &&[_, tiling, texture] : zip) {
        gl::Texture t = gl.getTexture(texture->texture_name);
        float width = (float) t.size.x;
        float height = (float) t.size.y;
        float winHeight = (float) raylib::GetRenderHeight();
        float ratio = winHeight / height;

        t.pos.y = 0;
        t.scale = ratio;
        for (std::size_t i = 0; i < tiling->repetitions; i++) {
            t.pos.x = (int) (ratio * width * (float) i + tiling->horizontal_pos);
            gl.draw(t);
        }
    }
}
