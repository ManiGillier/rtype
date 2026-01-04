/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** render horizontally tiled texture
*/

#include "Systems.hpp"

auto renderHTiledTexture([[maybe_unused]] Registry &r,
    containers::indexed_zipper<SparseArray<HorizontalTiling>,
                               SparseArray<TextureComp>> zip,
    TextureManager &manager)
-> void
{
    for (auto &&[_, tiling, texture] : zip) {
        Texture2D &openGlTexture = manager.getTexture(texture->texture_path);
        float width = (float) openGlTexture.width;

        for (std::size_t i = 0; i < tiling->repetitions; i++) {
            DrawTexture(openGlTexture, (int) (width * (float) i
                                              + tiling->horizontal_pos),
                        0, WHITE);
        }
    }
}
