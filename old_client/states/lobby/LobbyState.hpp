/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** client lobby state
*/

#ifndef CLIENT_LOBBY_STATE_HPP
#define CLIENT_LOBBY_STATE_HPP

#include "client/api/IGameState.hpp"
#include "client/manager/ClientManager.hpp"

class LobbyState : public IGameState
{
public:
    LobbyState(ClientManager &);

    auto update() -> State;
    auto render() -> void;
private:
    [[maybe_unused]] ClientManager &clientManager;
};

#endif /* CLIENT_LOBBY_STATE_HPP */
