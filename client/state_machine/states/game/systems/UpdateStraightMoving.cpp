/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** render square
*/

#include "ecs/regisrty/Registry.hpp"

#include "shared/components/Position.hpp"

#include "client/components/StraightMoving.hpp"

#include "client/state_machine/states/game/Game.hpp"
#include <cstdint>

auto updateStraightMoving([[maybe_unused]] Registry &reg,
    containers::indexed_zipper<SparseArray<Position>,
                               SparseArray<StraightMovingComp>> zip,
                  Game &state)
-> void
{
    for (auto &&[_, pos, move] : zip) {
        double dt = (state.getTime() - move->ms_time) / 1000.0;

        pos->x = (float) (move->pos_x_0 + move->vel_x * dt);
        pos->y = (float) (move->pos_y_0 + move->vel_y * dt);
    }
}
