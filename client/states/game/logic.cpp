/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** in game state logic
*/

#include "logic.hpp"

#include "shared/components/Position.hpp"

#include "client/components/Color.hpp"

#include "systems/Systems.hpp"

#include "shared/components/Health.hpp"
#include "shared/components/Dependence.hpp"

#include <iostream>
#include <cstddef>
#include <cstdint>
#include <memory>

#include "client/network/executor/NewPlayerExecutor.hpp"

InGameStateLogic::InGameStateLogic(IGameState &gs, NetworkManager &nm)
    : gameState(gs), networkManager(nm)
{
    //Registry &r = gameState.getRegistry();

    //r.add_component<Position>(this->player, {20, 20});
    //r.add_component<HitBox>(this->player, {20, 20});
    //r.add_component<SquareColor>(this->player, {WHITE});

    nm.addExecutor(std::make_unique<NewPlayerExecutor>(*this));
}

auto InGameStateLogic::update(Registry &r) -> void
{
    r.update();
}

auto InGameStateLogic::newPlayer(std::size_t id, std::size_t laser_id) -> void
{
    Registry &r = gameState.getRegistry();
    Entity player = r.spawn_entity();
    Entity laser = r.spawn_entity();

    (void) id;
    (void) laser_id;
    // TODO: implement sync
    r.add_component<Position>(player, {0, 0});
    r.add_component<HitBox>(player, {0, 0});
    r.add_component<SquareColor>(player, {WHITE});
    r.add_component<Health>(player, {0, 0});

    r.add_component<Dependence>(laser, {player.getId()});
}
