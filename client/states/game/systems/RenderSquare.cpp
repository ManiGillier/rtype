/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** render square
*/

#include "ecs/regisrty/Registry.hpp"

#include "shared/components/Position.hpp"
#include "client/components/Square.hpp"

#include <raylib.h>


auto renderSquare([[maybe_unused]] Registry &reg,
    containers::indexed_zipper<SparseArray<Position>,
                               SparseArray<Square>> zip)
-> void
{
    for (auto &&[_, pos, square] : zip) {
        DrawRectangle((int) pos->x, (int) pos->y,
                      (int) square->size, (int) square->size,
                      square->color);
    }
}
