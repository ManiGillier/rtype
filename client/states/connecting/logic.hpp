/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** in game state logic
*/

#ifndef CONNECTING_STATE_LOGIC_HPP
#define CONNECTING_STATE_LOGIC_HPP

#include "client/api/ILogic.hpp"
#include "client/api/IGameState.hpp"

#include "client/manager/NetworkManager.hpp"

#include <cstddef>
#include <optional>

#include "ecs/sync/Sync.hpp"

#include <vector>

class ConnectingStateLogic : public ILogic
{
public:
    ConnectingStateLogic(IGameState &gameState, NetworkManager &networkManager);

    auto update(Registry &) -> State;

    auto notifyAuthentified() -> void;
private:
    [[maybe_unused]] IGameState &gameState;
    [[maybe_unused]] NetworkManager &networkManager;

    [[maybe_unused]] State nextState = State::NONE;
    [[maybe_unused]] Sync sync;
    [[maybe_unused]] bool shouldStop = false;
};

#endif /* CONNECTING_STATE_LOGIC_HPP */
