/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** client menu state
*/

#ifndef CLIENT_MENU_STATE_HPP
#define CLIENT_MENU_STATE_HPP

#include "client/state_machine/State.hpp"

class Menu : public State {
public:
    Menu(ClientManager &cm, Registry &r, Sync &s);

    auto init_systems() -> void;
    auto init_entities() -> void;
private:
};

#endif /* CLIENT_MENU_STATE_HPP */
