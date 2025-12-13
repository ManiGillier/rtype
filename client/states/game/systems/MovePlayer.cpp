/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** move player
*/

#include "ecs/regisrty/Registry.hpp"

#include "client/components/Position.hpp"
#include "client/components/Player.hpp"

#include <iostream>
#include <raylib.h>

auto movePlayer(Registry &,
    containers::indexed_zipper<SparseArray<Position>,
                               SparseArray<PlayerControler>> zip)
-> void
{
    double dx = 0.0;
    double dy = 0.0;
    double speed = 20.0;

    if (IsKeyDown(KEY_LEFT))
        dx += -speed;
    if (IsKeyDown(KEY_RIGHT))
        dx += speed;
    if (IsKeyDown(KEY_DOWN))
        dy += -speed;
    if (IsKeyDown(KEY_UP))
        dy += speed;
    dx *= GetFrameTime();
    dy *= GetFrameTime();
    }
}
