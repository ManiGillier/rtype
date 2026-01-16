/*
** EPITECH PROJECT, 2026
** rype
** File description:
** login state
*/

#include "Login.hpp"

#include "client/network/executor/LoginExecutor.hpp"
#include "systems/Systems.hpp"

#include <iostream>
#include <memory>

#include "gui/LoginScene.hpp"

Login::Login(ClientManager &cm, Registry &r, Sync &s)
    : State(cm, r, s)
{}

auto Login::init_systems() -> void
{
    std::cout << "Init systems" << std::endl;

    this->guiScene = std::make_unique<LoginScene>(this->getGraphicalLibrary());
    this->guiScene->init();

    this->registry.reset_update_systems();
    this->registry.reset_render_systems();

    this->clientManager.getNetworkManager().resetExecutors();

    this->registry.add_global_update_system
        (login, std::ref(this->clientManager.getGui()),
         std::ref(this->clientManager.getNetworkManager()));
    this->registry.add_global_render_system
        (loginText, std::ref(this->clientManager.getGui()));

    this->clientManager.getNetworkManager()
        .addExecutor(std::make_unique<LoginResponseExecutor>(*this));
}

auto Login::init_entities() -> void
{
    std::cout << "Init entities" << std::endl;
}
