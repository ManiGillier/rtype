/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** in game state logic
*/

#include "logic.hpp"

#include "shared/components/Position.hpp"

#include "client/components/Color.hpp"


#include "shared/components/Health.hpp"
#include "shared/components/Dependence.hpp"
#include "shared/components/Laser.hpp"

#include <iostream>
#include <cstddef>
#include <cstdint>
#include <memory>

#include <network/packets/impl/ClientInputsPacket.hpp>

InGameStateLogic::InGameStateLogic(IGameState &gs, NetworkManager &nm)
    : gameState(gs), networkManager(nm)
{
}

auto InGameStateLogic::update(Registry &r) -> State_old
{
    r.update();
    this->managePlayerMovement();
    return this->shouldStop ? State_old::END_STATE : State_old::NONE;
}

auto InGameStateLogic::newPlayer(std::size_t, std::size_t)
-> void
{
}

auto InGameStateLogic::newEnemy(std::size_t) -> void
{
}

auto InGameStateLogic::newBullet(std::size_t) -> void
{
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

auto InGameStateLogic::updateHitbox(std::size_t id, float, float)
-> void
{
    std::optional<std::size_t> my_id = this->sync.get_mine_from_theirs(id);

    if (!my_id)
        return;
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
