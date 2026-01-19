/*
** EPITECH PROJECT, 2026
** rype
** File description:
** Win state
*/

#include "Win.hpp"

#include <iostream>
#include <memory>

#include "client/state_machine/states/menu/Menu.hpp"
#include "gui/WinScene.hpp"

#include "client/network/executor/SetAdminExecutor.hpp"

Win::Win(ClientManager &cm, Registry &r, Sync &s)
    : State(cm, r, s)
{}

auto Win::init_systems() -> void
{
    std::cout << "Init systems" << std::endl;

    this->guiScene =
        std::make_unique<WinScene>(this->getGraphicalLibrary(), *this);
    this->guiScene->init();

    this->registry.reset_update_systems();
    this->registry.reset_render_systems();

    this->clientManager.getNetworkManager().resetExecutors();

    this->clientManager.getNetworkManager()
        .addExecutor(std::make_unique<SetAdminExecutor>());

    // this->registry.add_global_update_system
    //     (gameStart, std::ref(this->clientManager.getGui()),
    //      std::ref(this->clientManager.getNetworkManager()));
    // this->registry.add_global_render_system
    //     (WinText, std::ref(this->clientManager.getGui()));
    // this->registry.add_global_render_system
    //     (WinPlayerList, std::ref(this->clientManager.getGui()),
    //      std::ref(*this));

    // this->clientManager.getNetworkManager()
    //     .addExecutor(std::make_unique<StartGameExecutor>(*this));
    // this->clientManager.getNetworkManager()
    //     .addExecutor(std::make_unique<NewPlayerExecutor>(*this));
}

auto Win::init_entities() -> void
{
    std::cout << "Init entities" << std::endl;
}

void Win::toMenu()
{
    this->change_state<Menu>();
}
