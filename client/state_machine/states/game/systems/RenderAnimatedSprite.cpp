/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** render animatedSprite
*/

#include "ecs/regisrty/Registry.hpp"

#include "shared/components/Position.hpp"
#include "shared/components/HitBox.hpp"

#include <graphical_library/api/GraphicalLibrary.hpp>

auto renderAnimatedSprite([[maybe_unused]] Registry &reg,
    containers::indexed_zipper<SparseArray<Position>,
                               SparseArray<HitBox>,
                               SparseArray<gl::AnimatedSprite>> zip,
                  gl::GraphicalLibrary &gl)
-> void
{
    int height = (int) gl.get_window_size().y;
    for (auto &&[_, pos, size, sprite] : zip) {
            gl::WorldPosition realPos = {
                (float) (pos->x - (size->height / 2.0)),
                (float) ((float) height - pos->y - (size->width / 2.0))
            };
        sprite->pos.x = (int) realPos.x;
        sprite->pos.y = (int) realPos.y;
        sprite->finalHeight = (int) size->height;
        gl.draw(std::ref(*sprite));
    }
}
