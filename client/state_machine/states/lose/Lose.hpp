/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** client Lose state
*/

#ifndef CLIENT_LOSE_STATE_HPP
#define CLIENT_LOSE_STATE_HPP

#include "client/state_machine/State.hpp"

class Lose : public State {
public:
    Lose(ClientManager &cm, Registry &r, Sync &s);

    auto init_systems() -> void;
    auto init_entities() -> void;
    auto toMenu() -> void;
};

#endif /* CLIENT_LOSE_STATE_HPP */
