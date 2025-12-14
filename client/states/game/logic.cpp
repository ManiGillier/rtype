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
#include "shared/components/Laser.hpp"

#include <iostream>
#include <cstddef>
#include <cstdint>
#include <memory>

#include "client/network/executor/NewPlayerExecutor.hpp"
#include "client/network/executor/NewEnemyExecutor.hpp"
#include "client/network/executor/NewBulletExecutor.hpp"
#include "client/network/executor/DespawnPlayerExecutor.hpp"

InGameStateLogic::InGameStateLogic(IGameState &gs, NetworkManager &nm)
    : gameState(gs), networkManager(nm)
{
    //Registry &r = gameState.getRegistry();

    //r.add_component<Position>(this->player, {20, 20});
    //r.add_component<HitBox>(this->player, {20, 20});
    //r.add_component<SquareColor>(this->player, {WHITE});

    nm.addExecutor(std::make_unique<NewPlayerExecutor>(*this));
    nm.addExecutor(std::make_unique<NewEnemyExecutor>(*this));
    nm.addExecutor(std::make_unique<NewBulletExecutor>(*this));
    nm.addExecutor(std::make_unique<DespawnPlayerExecutor>(*this));
}

auto InGameStateLogic::update(Registry &r) -> void
{
    r.update();
}

auto InGameStateLogic::newPlayer(std::size_t player_id, std::size_t laser_id)
-> void
{
    Registry &r = gameState.getRegistry();
    Entity player = r.spawn_entity();
    Entity laser = r.spawn_entity();

    this->sync.add(player.getId(), player_id);
    this->sync.add(laser.getId(), laser_id);
    r.add_component<Position>(player, {200, 500});
    r.add_component<HitBox>(player, {20, 20});
    r.add_component<ElementColor>(player, {WHITE});
    r.add_component<Health>(player, {0, 0});

    r.add_component<Dependence>(laser, {player.getId()});
    r.add_component<Laser>(laser, {10, 100});
    r.add_component<ElementColor>(laser, {GREEN});
}

auto InGameStateLogic::newEnemy(std::size_t enemy_id) -> void
{
    Registry &r = gameState.getRegistry();
    Entity enemy = r.spawn_entity();

    this->sync.add(enemy.getId(), enemy_id);
    r.add_component<Position>(enemy, {200, 200});
    r.add_component<HitBox>(enemy, {50, 50});
    r.add_component<ElementColor>(enemy, {ORANGE});
    r.add_component<Health>(enemy, {0, 0});
}

auto InGameStateLogic::newBullet(std::size_t bullet_id) -> void
{
    Registry &r = gameState.getRegistry();
    Entity bullet = r.spawn_entity();

    this->sync.add(bullet.getId(), bullet_id);
    r.add_component<Position>(bullet, {250, 200});
    r.add_component<HitBox>(bullet, {10, 10});
    r.add_component<ElementColor>(bullet, {BLUE});
}

auto InGameStateLogic::despawnPlayer(std::size_t player_id) -> void
{
    Registry &r = gameState.getRegistry();
    std::optional<std::size_t> my_id = this->sync.get_mine_from_theirs(player_id);
    this->sync.del_with_theirs(player_id);

    if (!my_id)
        return;
    r.kill_entity(r.entity_from_index(*my_id));
}
