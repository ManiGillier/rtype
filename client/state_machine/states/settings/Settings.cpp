/*
** EPITECH PROJECT, 2026
** rype
** File description:
** Settings state
*/

#include "Settings.hpp"

#include <iostream>
#include <memory>

#include "gui/SettingsScene.hpp"

#include "client/state_machine/states/menu/Menu.hpp"

Settings::Settings(ClientManager &cm, Registry &r, Sync &s)
    : State(cm, r, s)
{}

auto Settings::init_systems() -> void
{
    std::cout << "Init systems" << std::endl;

    this->guiScene =
        std::make_unique<SettingsScene>(this->getGraphicalLibrary(), *this);
    this->guiScene->init();

    this->registry.reset_update_systems();
    this->registry.reset_render_systems();

    this->clientManager.getNetworkManager().resetExecutors();

    // this->registry.add_global_update_system
    //     (gameStart, std::ref(this->clientManager.getGui()),
    //      std::ref(this->clientManager.getNetworkManager()));
    // this->registry.add_global_render_system
    //     (SettingsText, std::ref(this->clientManager.getGui()));
    // this->registry.add_global_render_system
    //     (SettingsPlayerList, std::ref(this->clientManager.getGui()),
    //      std::ref(*this));

    // this->clientManager.getNetworkManager()
    //     .addExecutor(std::make_unique<StartGameExecutor>(*this));
    // this->clientManager.getNetworkManager()
    //     .addExecutor(std::make_unique<NewPlayerExecutor>(*this));
}

auto Settings::init_entities() -> void
{
    std::cout << "Init entities" << std::endl;
}

auto Settings::toMenu() -> void
{
    this->change_state<Menu>();
}
