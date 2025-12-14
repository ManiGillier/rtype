/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** in game state logic
*/

#ifndef IN_GAME_STATE_LOGIC_HPP
#define IN_GAME_STATE_LOGIC_HPP

#include "client/api/ILogic.hpp"
#include "client/api/IGameState.hpp"

#include "client/manager/NetworkManager.hpp"

#include <cstddef>
#include <optional>

#include "ecs/sync/Sync.hpp"

#include <vector>

class InGameStateLogic : public ILogic
{
public:
    InGameStateLogic(IGameState &gameState, NetworkManager &networkManager);

    auto update(Registry &) -> void;

    auto newPlayer(std::size_t player_id, std::size_t laser_id) -> void;
    auto newEnemy(std::size_t enemy_id) -> void;
    auto newBullet(std::size_t bullet_id) -> void;
    auto despawnEntity(std::size_t id) -> void;
private:
    IGameState &gameState;
    NetworkManager &networkManager;

    Sync sync;
};

#endif /* IN_GAME_STATE_LOGIC_HPP */
