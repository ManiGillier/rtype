/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** render square
*/

#include "ecs/regisrty/Registry.hpp"

#include "shared/components/Position.hpp"
#include "shared/components/HitBox.hpp"
#include "client/components/Color.hpp"

#include "client/graphical_library/GraphicalLibrary.hpp"

#include <raylib.h>

auto renderSquare([[maybe_unused]] Registry &reg,
    containers::indexed_zipper<SparseArray<Position>,
                               SparseArray<HitBox>,
                               SparseArray<ElementColor>> zip,
                  gl::GraphicalLibrary &gl)
-> void
{
    int height = GetRenderHeight();
    for (auto &&[_, pos, size, square_color] : zip) {
        gl.draw(gl::Rectangle {
            gl::WorldPosition {
                (float) (pos->x - (size->height / 2.0)),
                (float) ((float) height - pos->y - (size->width / 2.0))
            },
            gl::Vector2ui {
                (std::uint32_t) size->height,
                (std::uint32_t) size->width
            },
            square_color->color
        });
    }
}
