/*
** EPITECH PROJECT, 2026
** rype
** File description:
** menu state
*/

#include "Menu.hpp"

#include "client/network/executor/JoinedLobbyExecutor.hpp"
#include "gui/Scene.hpp"
#include "systems/Systems.hpp"

#include <iostream>
#include <memory>

Menu::Menu(ClientManager &cm, Registry &r, Sync &s)
    : State(cm, r, s)
{}

auto Menu::init_systems() -> void
{
    std::cout << "Init systems" << std::endl;

    this->guiScene = std::make_unique<MenuScene>(this->getGraphicalLibrary(),
                                                 *this);
    this->guiScene->init();


    this->registry.reset_update_systems();
    this->registry.reset_render_systems();

    this->clientManager.getNetworkManager().resetExecutors();

    this->registry.add_global_update_system
        (menu, std::ref(this->clientManager.getGui()),
         std::ref(this->clientManager.getNetworkManager()));

    this->clientManager.getNetworkManager()
        .addExecutor(std::make_unique<JoinedLobbyExecutor>(*this));
}

auto Menu::init_entities() -> void
{
    std::cout << "Init entities" << std::endl;
}
