/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** client game state
*/

#ifndef CLIENT_GAME_STATE_HPP
#define CLIENT_GAME_STATE_HPP

#include "client/state_machine/State.hpp"

#include <cstddef>
#include <cstdint>
#include <map>
#include <optional>
#include <vector>

#include <network/packets/impl/LaserActiveUpdatePacket.hpp>
#include <network/packets/impl/PositionUpdatePacket.hpp>
#include <network/packets/impl/LinkPlayersPacket.hpp>
#include <network/packets/impl/SpawnStraightMovingEntityPacket.hpp>
#include <network/packets/impl/ClientInputsPacket.hpp>
#include <network/packets/impl/StartGamePacket.hpp>

class Game : public State {
public:
    Game(ClientManager &cm, Registry &r, Sync &s, GameStartConfig config);

    auto init_systems() -> void;
    auto init_entities() -> void;

    auto getTime() -> uint32_t;
    auto setTime(uint32_t) -> void;
    auto newPlayers(std::vector<PlayerLink> data) -> void;
    auto newPlayer(std::string name, std::size_t player_id,
                   std::size_t laser_id) -> void;
    auto newEnemy(std::size_t enemy_id) -> void;
    auto newBullet(std::vector<StraightMovingEntity>) -> void;
    auto destroyEntities(std::vector<uint16_t> ids) -> void;
    auto despawnEntity(std::size_t id) -> void;
    auto registerClientId(std::size_t id) -> void;
    // auto end() -> void;
    auto updateHealth(std::size_t id, float health, float max_health) -> void;
    auto updateHitbox(std::size_t id, float width, float height) -> void;
    auto updateLaser(std::size_t id, bool active, float length) -> void;
    auto updatePosition(std::size_t id, float x, float y) -> void;
    auto updatePositions(std::vector<PositionData> data) -> void;
    auto updateLasers(std::vector<LaserData> data) -> void;
    auto getLastClientInputs() -> ClientInputs;
    auto setLastClientInputs(ClientInputs) -> void;

    auto getMaxHealth() -> int;
    auto getCurrentHealth() -> int;
    auto hit() -> void;
    auto getPlayerList() -> std::vector<std::pair<std::string, bool>>;

    auto getChatMessage(int id) -> std::string;
    auto addChatMessage(std::string message) -> void;
    auto sendNewMessage() -> void;
    auto setMessage(std::string message) -> void;
    auto getMessage() -> std::string;
private:
    GameStartConfig config;
    int lifeRemaining;
    std::map<std::size_t, std::pair<std::string, bool>> players;
    std::optional<std::size_t> clientId = std::nullopt;
    uint32_t startTime = 0;
    ClientInputs lastClientInputs = { .byte = 0 };
    std::array<std::string, 10> messages;
    std::string messageToSend = "";
};

#endif /* CLIENT_GAME_STATE_HPP */
