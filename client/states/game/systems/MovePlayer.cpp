/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** move player
*/

#include "ecs/regisrty/Registry.hpp"

#include "client/components/Position.hpp"
#include "client/components/Player.hpp"

#include <tuple>
#include <unordered_map>

#include <raylib.h>

#include <iostream>

auto movePlayer(Registry &,
    std::unordered_map<std::size_t, std::tuple<Position*, PlayerControler*>> map)
-> void
{
    double dx = 0.0;
    double dy = 0.0;
    double speed = 1.0;

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
    for (auto [_, tuple] : map) {
        Position &pos = *std::get<Position*>(tuple);
        pos.x += (float) dx;
        pos.y += (float) dy;
        std::cout << pos.x << " " << pos.y << std::endl;
    }
}
