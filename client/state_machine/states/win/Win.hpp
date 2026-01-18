/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** client Win state
*/

#ifndef CLIENT_WIN_STATE_HPP
#define CLIENT_WIN_STATE_HPP

#include "client/state_machine/State.hpp"

class Win : public State {
public:
    Win(ClientManager &cm, Registry &r, Sync &s);

    auto init_systems() -> void;
    auto init_entities() -> void;
private:
};

#endif /* CLIENT_WIN_STATE_HPP */
