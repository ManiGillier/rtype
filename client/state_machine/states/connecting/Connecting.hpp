/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** client connecting state
*/

#ifndef CLIENT_CONNECTING_STATE_HPP
#define CLIENT_CONNECTING_STATE_HPP

#include "client/state_machine/State.hpp"

class Connecting : public State {
public:
    Connecting(ClientManager &cm, Registry &r, Sync &s);

    auto init_systems() -> void;
    auto init_entities() -> void;
private:
};

#endif /* CLIENT_CONNECTING_STATE_HPP */
