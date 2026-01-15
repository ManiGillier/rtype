/*
** EPITECH PROJECT, 2026
** rype
** File description:
** lobby state
*/

#include "Lobby.hpp"

#include "client/network/executor/StartGameExecutor.hpp"
#include "client/network/executor/NewPlayerExecutor.hpp"
#include "systems/Systems.hpp"

#include <iostream>
#include <memory>

#include "gui/LobbyScene.hpp"

Lobby::Lobby(ClientManager &cm, Registry &r, Sync &s, std::string code)
    : State(cm, r, s), code(code)
{}

auto Lobby::init_systems() -> void
{
    std::cout << "Init systems" << std::endl;

    this->guiScene =
        std::make_unique<LobbyScene>(this->getGraphicalLibrary());
    this->guiScene->init();

    this->registry.reset_update_systems();
    this->registry.reset_render_systems();

    this->clientManager.getNetworkManager().resetExecutors();

    this->registry.add_global_update_system
        (gameStart, std::ref(this->clientManager.getGui()),
         std::ref(this->clientManager.getNetworkManager()));
    this->registry.add_global_render_system
        (lobbyText, std::ref(this->clientManager.getGui()));
    this->registry.add_global_render_system
        (lobbyPlayerList, std::ref(this->clientManager.getGui()),
         std::ref(*this));

    this->clientManager.getNetworkManager()
        .addExecutor(std::make_unique<StartGameExecutor>(*this));
    this->clientManager.getNetworkManager()
        .addExecutor(std::make_unique<NewPlayerExecutor>(*this));
}

auto Lobby::init_entities() -> void
{
    std::cout << "Init entities" << std::endl;
}

auto Lobby::updatePlayers(std::vector<std::string> playerList) -> void
{
    this->playerList = playerList;
}

auto Lobby::getPlayerList() -> std::vector<std::string>
{
    return this->playerList;
}
