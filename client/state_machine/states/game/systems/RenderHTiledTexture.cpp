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
    TextureManager &manager)
-> void
{
    for (auto &&[_, tiling, texture] : zip) {
        gl::Texture &t = manager.getTexture(texture->texture_path);
        float width = (float) t.getWidth();
        float height = (float) t.getHeight();
        float winHeight = (float) raylib::GetRenderHeight();
        float ratio = winHeight / height;

        for (std::size_t i = 0; i < tiling->repetitions; i++) {
            t.draw(gl::WorldPosition {
                (ratio * width * (float) i + tiling->horizontal_pos),
                0}, 0, ratio);
        }
    }
}
