/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** in game state logic
*/

#ifndef LOBBY_STATE_LOGIC_HPP
#define LOBBY_STATE_LOGIC_HPP

#include "client/api/ILogic.hpp"
#include "client/api/IGameState.hpp"

#include "client/manager/NetworkManager.hpp"

#include <cstddef>
#include <optional>

#include "ecs/sync/Sync.hpp"

#include <vector>

class LobbyStateLogic : public ILogic
{
public:
    LobbyStateLogic(IGameState &gameState, NetworkManager &networkManager);

    auto update(Registry &) -> State_old;

    auto startGame() -> void;
private:
    [[maybe_unused]] IGameState &gameState;
    [[maybe_unused]] NetworkManager &networkManager;

    [[maybe_unused]] State_old nextState = State_old::NONE;
    [[maybe_unused]] Sync sync;
    [[maybe_unused]] bool shouldStop = false;
};

#endif /* LOBBY_STATE_LOGIC_HPP */
