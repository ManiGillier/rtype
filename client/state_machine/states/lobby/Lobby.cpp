/*
** EPITECH PROJECT, 2026
** rype
** File description:
** lobby state
*/

#include "Lobby.hpp"

#include "client/network/executor/StartGameExecutor.hpp"
#include "systems/Systems.hpp"

#include <iostream>
#include <memory>

Lobby::Lobby(ClientManager &cm, Registry &r, Sync &s)
    : State(cm, r, s)
{}

auto Lobby::init_systems() -> void
{
    std::cout << "Init systems" << std::endl;
    this->registry.reset_update_systems();
    this->registry.reset_render_systems();

    this->registry.add_global_update_system
        (gameStart, std::ref(this->clientManager.getNetworkManager()));
    this->registry.add_global_render_system
        (lobbyText, std::ref(this->clientManager.getGui()));

    this->clientManager.getNetworkManager()
        .addExecutor(std::make_unique<StartGameExecutor>(*this));
}

auto Lobby::init_entities() -> void
{
    std::cout << "Init entities" << std::endl;
}
