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
#include "client/network/executor/DespawnBulletExecutor.hpp"
#include "client/network/executor/EnemyDiedExecutor.hpp"
#include "client/network/executor/PlayerIdExecutor.hpp"
#include "client/network/executor/GameOverExecutor.hpp"
#include "client/network/executor/HealthUpdateExecutor.hpp"
#include "client/network/executor/HitboxSizeUpdateExecutor.hpp"
#include "client/network/executor/LaserActivateUpdateExecutor.hpp"
#include "client/network/executor/PositionUpdateExecutor.hpp"
#include <network/packets/impl/ClientInputsPacket.hpp>

InGameStateLogic::InGameStateLogic(IGameState &gs, NetworkManager &nm)
    : gameState(gs), networkManager(nm)
{
    nm.addExecutor(std::make_unique<NewPlayerExecutor>(*this));
    nm.addExecutor(std::make_unique<NewEnemyExecutor>(*this));
    nm.addExecutor(std::make_unique<NewBulletExecutor>(*this));
    nm.addExecutor(std::make_unique<DespawnPlayerExecutor>(*this));
    nm.addExecutor(std::make_unique<DespawnBulletExecutor>(*this));
    nm.addExecutor(std::make_unique<EnemyDiedExecutor>(*this));
    nm.addExecutor(std::make_unique<PlayerIdExecutor>(*this));
    nm.addExecutor(std::make_unique<GameOverExecutor>(*this));
    nm.addExecutor(std::make_unique<HealthUpdateExecutor>(*this));
    nm.addExecutor(std::make_unique<HitboxSizeUpdateExecutor>(*this));
    nm.addExecutor(std::make_unique<LaserActiveUpdateExecutor>(*this));
    nm.addExecutor(std::make_unique<PositionUpdateExecutor>(*this));
}

auto InGameStateLogic::update(Registry &r) -> State
{
    r.update();
    this->managePlayerMovement();
    return this->shouldStop ? State::END_STATE : State::NONE;
}

auto InGameStateLogic::newPlayer(std::size_t player_id, std::size_t laser_id)
-> void
{
    Registry &r = gameState.getRegistry();
    Entity player = r.spawn_entity();
    Entity laser = r.spawn_entity();

    this->sync.add(player.getId(), player_id);
    this->sync.add(laser.getId(), laser_id);
    r.add_component<Position>(player, {-200, -500});
    r.add_component<HitBox>(player, {20, 20});
    r.add_component<ElementColor>(player, {gl::WHITE});
    r.add_component<Health>(player, {0, 0});
    r.add_component<PlayerId>(player, {this->playerId});
    this->playerId++;

    r.add_component<Dependence>(laser, {player.getId()});
    r.add_component<Laser>(laser, {true, 30});
    r.add_component<ElementColor>(laser, {gl::GREEN});
}

auto InGameStateLogic::newEnemy(std::size_t enemy_id) -> void
{
    Registry &r = gameState.getRegistry();
    Entity enemy = r.spawn_entity();

    this->sync.add(enemy.getId(), enemy_id);
    r.add_component<Position>(enemy, {-200, -200});
    r.add_component<HitBox>(enemy, {50, 50});
    r.add_component<ElementColor>(enemy, {gl::MAGENTA});
    r.add_component<Health>(enemy, {0, 0});
}

auto InGameStateLogic::newBullet(std::size_t bullet_id) -> void
{
    Registry &r = gameState.getRegistry();
    Entity bullet = r.spawn_entity();

    this->sync.add(bullet.getId(), bullet_id);
    r.add_component<Position>(bullet, {-250, -200});
    r.add_component<HitBox>(bullet, {10, 10});
    r.add_component<ElementColor>(bullet, {gl::BLUE});
}

auto InGameStateLogic::despawnEntity(std::size_t id) -> void
{
    Registry &r = gameState.getRegistry();
    std::optional<std::size_t> my_id = this->sync.get_mine_from_theirs(id);
    this->sync.del_with_theirs(id);

    if (!my_id)
        return;
    r.kill_entity(r.entity_from_index(*my_id));
}

auto InGameStateLogic::registerClientId(std::size_t id) -> void
{
    this->clientId = this->sync.get_mine_from_theirs(id);

    if (!this->clientId)
        return;
}

auto InGameStateLogic::end() -> void
{
    this->shouldStop = true;
}

auto InGameStateLogic::updateHealth(std::size_t id, float health,
                                    float max_health) -> void
{
    std::optional<std::size_t> my_id = this->sync.get_mine_from_theirs(id);

    if (!my_id)
        return;
    this->gameState.getRegistry().set<Health>(*my_id, (int) health,
                                              (int) max_health);
}

auto InGameStateLogic::updateHitbox(std::size_t id, float width, float height)
-> void
{
    std::optional<std::size_t> my_id = this->sync.get_mine_from_theirs(id);

    if (!my_id)
        return;
    this->gameState.getRegistry().set<HitBox>(*my_id, width, height);
}

auto InGameStateLogic::updateLaser(std::size_t id, bool active, float length)
-> void
{
    std::optional<std::size_t> my_id = this->sync.get_mine_from_theirs(id);

    if (!my_id)
        return;
    this->gameState.getRegistry().set<Laser>(*my_id, active, length);
}

namespace raylib {
    #include <raylib.h>
}

auto InGameStateLogic::managePlayerMovement() -> void
{
    ClientInputs clientInputs = {0};

    clientInputs.value.left = IsKeyDown(raylib::KEY_LEFT)
                              || IsKeyDown(raylib::KEY_Q);
    clientInputs.value.right = IsKeyDown(raylib::KEY_RIGHT)
                               || IsKeyDown(raylib::KEY_D);
    clientInputs.value.up = IsKeyDown(raylib::KEY_UP)
                            || IsKeyDown(raylib::KEY_Z);
    clientInputs.value.down = IsKeyDown(raylib::KEY_DOWN)
                              || IsKeyDown(raylib::KEY_S);
    clientInputs.value.shoot = IsKeyDown(raylib::KEY_SPACE)
                               || IsMouseButtonDown(raylib::MOUSE_BUTTON_LEFT);

    this->networkManager
        .sendPacket(std::make_shared<ClientInputsPacket>(clientInputs));
}

auto InGameStateLogic::updatePosition(std::size_t id, float x, float y)
-> void
{
    std::optional<std::size_t> my_id = this->sync.get_mine_from_theirs(id);

    if (!my_id) {
        return;
    }
    this->gameState.getRegistry().set<Position>(*my_id, x, y);
}
