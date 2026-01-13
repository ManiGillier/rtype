/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** client game state
*/

#ifndef CLIENT_GAME_STATE_HPP
#define CLIENT_GAME_STATE_HPP

#include "client/state_machine/State.hpp"

#include <optional>

class Game : public State {
public:
    Game(ClientManager &cm, Registry &r, Sync &s);

    auto init_systems() -> void;
    auto init_entities() -> void;

    auto newPlayer(std::size_t player_id, std::size_t laser_id) -> void;
    auto newEnemy(std::size_t enemy_id) -> void;
    auto newBullet(std::size_t bullet_id) -> void;
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
};

#endif /* CLIENT_GAME_STATE_HPP */
