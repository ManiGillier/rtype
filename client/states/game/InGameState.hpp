/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** in game game state
*/

#ifndef IN_GAME_STATE_HPP
#define IN_GAME_STATE_HPP

#include "client/api/IGameState.hpp"
#include "client/manager/ClientManager.hpp"

class InGameState : public IGameState {
public:
    InGameState(ClientManager &);

    auto update() -> State;
    auto render() -> void;
private:
    ClientManager &clientManager;
};

#endif /* IN_GAME_STATE_HPP */
