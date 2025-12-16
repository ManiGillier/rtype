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
    IGameState &gameState;
    NetworkManager &networkManager;

    State nextState = State::NONE;
    Sync sync;
    bool shouldStop = false;
};

#endif /* CONNECTING_STATE_LOGIC_HPP */
