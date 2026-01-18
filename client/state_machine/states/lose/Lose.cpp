/*
** EPITECH PROJECT, 2026
** rype
** File description:
** Lose state
*/

#include "Lose.hpp"

#include <iostream>
#include <memory>

#include "client/manager/ClientManager.hpp"
#include "client/state_machine/State.hpp"
#include "client/state_machine/states/menu/Menu.hpp"
#include "gui/LoseScene.hpp"

Lose::Lose(ClientManager &cm, Registry &r, Sync &s)
    : State(cm, r, s)
{}

auto Lose::init_systems() -> void
{
    std::cout << "Init systems" << std::endl;

    this->guiScene =
        std::make_unique<LoseScene>(this->getGraphicalLibrary(), *this);
    this->guiScene->init();

    this->registry.reset_update_systems();
    this->registry.reset_render_systems();

    this->clientManager.getNetworkManager().resetExecutors();

    // this->registry.add_global_update_system
    //     (gameStart, std::ref(this->clientManager.getGui()),
    //      std::ref(this->clientManager.getNetworkManager()));
    // this->registry.add_global_render_system
    //     (LoseText, std::ref(this->clientManager.getGui()));
    // this->registry.add_global_render_system
    //     (LosePlayerList, std::ref(this->clientManager.getGui()),
    //      std::ref(*this));

    // this->clientManager.getNetworkManager()
    //     .addExecutor(std::make_unique<StartGameExecutor>(*this));
    // this->clientManager.getNetworkManager()
    //     .addExecutor(std::make_unique<NewPlayerExecutor>(*this));
}

auto Lose::init_entities() -> void
{
    std::cout << "Init entities" << std::endl;
}

void Lose::toMenu()
{
    this->change_state<Menu>();
}
