/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** client settings state
*/

#ifndef CLIENT_SETTINGS_STATE_HPP
#define CLIENT_SETTINGS_STATE_HPP

#include "client/state_machine/State.hpp"

class Settings : public State {
public:
    Settings(ClientManager &cm, Registry &r, Sync &s);

    auto init_systems() -> void;
    auto init_entities() -> void;
private:
};

#endif /* CLIENT_SETTINGS_STATE_HPP */
