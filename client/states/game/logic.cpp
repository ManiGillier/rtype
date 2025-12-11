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

    //r.add_update_system<Position, PlayerControler>(movePlayer);
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

auto InGameStateLogic::update(Registry &r, EventManager &eventManager) -> void
{
    test test;
    test.left = eventManager.getEvent(EventId::LEFT).getState().isActivated();
    test.right = eventManager.getEvent(EventId::RIGHT).getState().isActivated();
    test.up = eventManager.getEvent(EventId::UP).getState().isActivated();
    test.down = eventManager.getEvent(EventId::DOWN).getState().isActivated();
    test.shoot = eventManager.getEvent(EventId::SHOOT).getState().isActivated();
    test_2 test_2;
    test_2.test = test;
    for (std::size_t i = 0; i < 5; i++)
        std::cout << ((test_2.value & (1 << i)) ? "1" : "0");
    std::cout << std::endl;
    r.update();
}
