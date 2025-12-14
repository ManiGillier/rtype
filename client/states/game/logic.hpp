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

#include <vector>

class InGameStateLogic : public ILogic
{
public:
    InGameStateLogic(IGameState &gameState, NetworkManager &networkManager);

    auto update(Registry &) -> void;

    auto newPlayer(std::size_t id, std::size_t laser_id) -> void;
private:
    IGameState &gameState;
    NetworkManager &networkManager;

    // TODO: implement sync
    std::vector<Entity> players;
};

#endif /* IN_GAME_STATE_LOGIC_HPP */
