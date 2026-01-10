/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** connecting state logic
*/

#include "logic.hpp"

#include "client/network/executor/AuthentifiedPacketExecutor.hpp"

#include <iostream>
#include <memory>

ConnectingStateLogic::ConnectingStateLogic(IGameState &gs, NetworkManager &nm)
    : gameState(gs), networkManager(nm)
{
}

auto ConnectingStateLogic::update(Registry &r) -> State_old
{
    r.update();
    return this->nextState;
}

auto ConnectingStateLogic::notifyAuthentified() -> void
{
    this->nextState = State_old::LOBBY;
}
