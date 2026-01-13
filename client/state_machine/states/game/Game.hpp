/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** client game state
*/

#ifndef CLIENT_GAME_STATE_HPP
#define CLIENT_GAME_STATE_HPP

#include "client/state_machine/State.hpp"

#include <cstdint>
#include <optional>
#include <vector>

#include <network/packets/impl/SpawnStraightMovingEntityPacket.hpp>

class Game : public State {
public:
    Game(ClientManager &cm, Registry &r, Sync &s);

    auto init_systems() -> void;
    auto init_entities() -> void;

    auto getTime() -> uint32_t;
    auto setTime(uint32_t) -> void;
    auto newPlayer(std::size_t player_id, std::size_t laser_id) -> void;
    auto newEnemy(std::size_t enemy_id) -> void;
    auto newBullet(std::vector<StraightMovingEntity>) -> void;
    auto despawnEntity(std::size_t id) -> void;
    auto registerClientId(std::size_t id) -> void;
    // auto end() -> void;
    auto updateHealth(std::size_t id, float health, float max_health) -> void;
    auto updateHitbox(std::size_t id, float width, float height) -> void;
    auto updateLaser(std::size_t id, bool active, float length) -> void;
    auto updatePosition(std::size_t id, float x, float y) -> void;
private:
    std::size_t playerId = 0;
    std::optional<std::size_t> clientId = std::nullopt;
    uint32_t startTime = 0;
};

#endif /* CLIENT_GAME_STATE_HPP */
