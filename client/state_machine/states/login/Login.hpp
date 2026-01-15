/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** client login state
*/

#ifndef CLIENT_LOGIN_STATE_HPP
#define CLIENT_LOGIN_STATE_HPP

#include "client/state_machine/State.hpp"

class Login : public State {
public:
    Login(ClientManager &cm, Registry &r, Sync &s);

    auto init_systems() -> void;
    auto init_entities() -> void;
private:
};

#endif /* CLIENT_LOGIN_STATE_HPP */
