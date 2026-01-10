/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** game state
*/

#include "Game.hpp"

Game::Game(ClientManager &cm, Registry &r, Sync &s)
    : State(cm, r, s)
{}

auto Game::init_systems() -> void
{
    this->registry.reset_update_systems();
    this->registry.reset_render_systems();
    this->clientManager.getNetworkManager().resetExecutors();
}

auto Game::init_entities() -> void {}
