/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** render laser
*/

#include "ecs/regisrty/Registry.hpp"

#include "Systems.hpp"

#include <raylib.h>


auto renderLaser([[maybe_unused]] Registry &reg,
    containers::indexed_zipper<SparseArray<Laser>,
                               SparseArray<Dependence>,
                               SparseArray<ElementColor>> zip)
-> void
{
    for (auto &&[_, laser, ref, color] : zip) {
        std::optional<Position> player_pos = reg.get<Position>(ref->id);

        if (!player_pos)
            continue;
        DrawRectangle((int) (player_pos->x - laser->width / 2),
                      (int) player_pos->y,
                      (int) laser->width, (int) laser->height,
                      color->color);
    }
}
