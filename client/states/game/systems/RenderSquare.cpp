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

#include <raylib.h>


auto renderSquare([[maybe_unused]] Registry &reg,
    containers::indexed_zipper<SparseArray<Position>,
                               SparseArray<HitBox>,
                               SparseArray<SquareColor>> zip)
-> void
{
    for (auto &&[_, pos, size, square_color] : zip) {
        DrawRectangle((int) pos->x, (int) pos->y,
                      (int) size->height, (int) size->width,
                      square_color->color);
    }
}
