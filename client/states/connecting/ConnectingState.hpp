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

#include <graphical_library/api/GraphicalLibrary.hpp>

class ConnectingState : public IGameState
{
public:
    ConnectingState(ClientManager &);

    auto update() -> State;
    auto render() -> void;

    auto getGraphicalLibrary() -> gl::GraphicalLibrary &;
private:
    [[maybe_unused]] ClientManager &clientManager;
};

#endif /* CLIENT_CONNECTING_STATE_HPP */
