/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** client connecting state
*/

#ifndef CLIENT_CONNECTING_STATE_HPP
#define CLIENT_CONNECTING_STATE_HPP

#include "client/api/IGameState.hpp"
#include "client/manager/ClientManager.hpp"

class ConnectingState : public IGameState
{
public:
    ConnectingState(ClientManager &);

    auto update() -> State;
    auto render() -> void;
private:
    ClientManager &clientManager;
};

#endif /* CLIENT_CONNECTING_STATE_HPP */
