/*
** EPITECH PROJECT, 2026
** rype
** File description:
** lobby state
*/

#include "Lobby.hpp"

#include "systems/Systems.hpp"

#include <iostream>

Lobby::Lobby(ClientManager &cm, Registry &r)
    : State(cm, r)
{}

auto Lobby::init_systems() -> void
{
    std::cout << "Init systems" << std::endl;
    this->registry.add_global_update_system
        (gameStart, std::ref(this->clientManager.getNetworkManager()));
}

auto Lobby::init_entities() -> void
{
    std::cout << "Init entities" << std::endl;
}
