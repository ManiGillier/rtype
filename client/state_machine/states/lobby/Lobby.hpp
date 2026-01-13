/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** client lobby state
*/

#ifndef CLIENT_LOBBY_STATE_HPP
#define CLIENT_LOBBY_STATE_HPP

#include "client/state_machine/State.hpp"

class Lobby : public State {
public:
    Lobby(ClientManager &cm, Registry &r, Sync &s);

    auto init_systems() -> void;
    auto init_entities() -> void;
private:
};

#endif /* CLIENT_LOBBY_STATE_HPP */
