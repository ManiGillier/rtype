/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** render square
*/

#include "ecs/regisrty/Registry.hpp"

#include "client/components/Position.hpp"
#include "client/components/Square.hpp"

#include <tuple>
#include <unordered_map>

#include <raylib.h>
/*
auto renderSquare([[maybe_unused]] Registry &reg,
    std::unordered_map<std::size_t, std::tuple<Position, Square>> items)
-> void
{
    for (auto &&[i, item] : items) {
        Position &pos = std::get<Position>(item);
        Square &square = std::get<Square>(item);
        DrawRectangle((int) pos.x, (int) pos.y,
                      (int) square.size, (int) square.size,
                      WHITE);
    }
}
*/
