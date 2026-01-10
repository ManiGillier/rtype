/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** lobby state logic
*/

#include "logic.hpp"

#include "client/network/executor/StartGameExecutor.hpp"

//#include "systems/Systems.hpp"
#include <iostream>
#include <memory>

LobbyStateLogic::LobbyStateLogic(IGameState &gs, NetworkManager &nm)
    : gameState(gs), networkManager(nm)
{
    //Registry &r = this->gameState.getRegistry();

    //r.add_global_update_system(gameStart, std::ref(this->networkManager));
    this->networkManager.addExecutor(std::make_unique<StartGameExecutor>(*this));
}

auto LobbyStateLogic::update(Registry &r) -> State_old
{
    r.update();
    return this->nextState;
}

auto LobbyStateLogic::startGame() -> void
{
    this->nextState = State_old::IN_GAME;
}
