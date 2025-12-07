/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** in game state logic
*/

#include "logic.hpp"

#include "client/components/Position.hpp"
#include "client/components/Square.hpp"

InGameStateLogic::InGameStateLogic(Registry &r)
{
    this->square = r.spawn_entity();
    r.add_component<Position>(this->square.value(), {20, 20});
    r.add_component<Square>(this->square.value(), {100});
}

auto InGameStateLogic::update(Registry &r) -> void
{
    r.update();
}
