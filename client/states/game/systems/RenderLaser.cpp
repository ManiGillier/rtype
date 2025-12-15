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
        if (!laser->active)
            continue;
        int const laser_width = 5;
        DrawRectangle((int) (player_pos->x - (float) laser_width / 2),
                      (int) player_pos->y,
                      laser_width, (int) laser->length,
                      color->color);
    }
}
