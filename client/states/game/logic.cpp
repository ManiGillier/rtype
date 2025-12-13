/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** in game state logic
*/

#include "logic.hpp"

#include "client/components/Position.hpp"
#include "client/components/Square.hpp"
#include "client/components/Player.hpp"

#include "systems/Systems.hpp"

#include <iostream>
#include <cstddef>
#include <cstdint>

InGameStateLogic::InGameStateLogic(IGameState &gs)
    : gameState(gs), player(gameState.getRegistry().spawn_entity())
{
    Registry &r = gameState.getRegistry();

    r.add_update_system<Position, PlayerControler>(movePlayer);
    r.add_component<Position>(this->player, {20, 20});
    r.add_component<Square>(this->player, {100});
    r.add_component<PlayerControler>(this->player, {});
}

struct test {
    uint8_t left : 1;
    uint8_t right : 1;
    uint8_t up : 1;
    uint8_t down : 1;
    uint8_t shoot : 1;
    uint8_t : 3;
};

union test_2 {
    struct test test;
    uint8_t value;
};

auto InGameStateLogic::update(Registry &r) -> void
{
    r.update();
}
