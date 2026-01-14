/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** client manager
*/

#include "ClientManager.hpp"

#include <graphical_library/raylib/InitGraphicalLibrary.hpp>

#include "client/state_machine/states/connecting/Connecting.hpp"

/*#include "client/states/game/InGameState.hpp"
#include "client/states/lobby/LobbyState.hpp"
#include "client/states/connecting/ConnectingState.hpp"*/

#include <iostream>
#include <network/logger/Logger.hpp>

#include <cstdlib>
#include <memory>

ClientManager::ClientManager()
    : stateMachine(std::make_unique<Connecting>
        (*this, this->registry, this->sync))
{
    this->gui = init_raylib();

    this->gui->init();

    this->gui->registerTexture("client/assets/background.jpg", "background");
    this->gui->registerSound("client/assets/laser.mp3", "laser");
    this->gui->registerSound("client/assets/new_player.mp3", "new_player");
    this->gui->registerSound("client/assets/despawn_player.mp3",
                             "despawn_player");

    this->gui->registerEvent("start_game", gl::Key::SPACE);
    this->gui->registerEvent("shoot", gl::Key::SPACE);
    this->gui->registerEvent("move_left", gl::Key::ARROW_LEFT);
    this->gui->registerEvent("move_right", gl::Key::ARROW_RIGHT);
    this->gui->registerEvent("move_up", gl::Key::ARROW_UP);
    this->gui->registerEvent("move_down", gl::Key::ARROW_DOWN);
}

/*
inline auto ClientManager::changeInternalState(std::unique_ptr<IGameState> state)
-> void
{
    this->_internal_state = std::move(state);
}
*/

/*
auto ClientManager::changeState(const State_old state) -> void
{
    this->networkManager->resetExecutors();
    this->changeInternalState(this->_gameStateFactory[state]());
    this->_state = state;
}
*/

auto ClientManager::launch(int argc, char **argv) -> void
{
    if (argc != 3 && argc != 4) {
        std::cerr << "Usage:" << std::endl
        << argv[0] << "\tip port [-d]" << std::endl;
        return;
    }
    if (argc == 4 && std::string(argv[5]) == "-d")
        Logger::shouldLog = true;
    this->networkManager =
        std::make_unique<NetworkManager>(argv[1], std::atoi(argv[2]));

    LOG("Starting game.");
    this->gui->loadEverything();
    this->stateMachine.init();
    this->loop();
}

auto ClientManager::loop() -> void
{
    while (true) {
        if (this->networkManager->isStopped())
            break;
        this->networkManager->getClient().executePackets();
        this->getGui().start_new_frame();
        if (this->stateMachine.update()) {
            this->getGui().end_frame();
            break;
        }
        this->getGui().end_frame();
        if (this->getGui().should_close())
            break;
    }
    this->unload();
}

auto ClientManager::unload() -> void
{
    LOG("Unloading.");
    this->gui->deinit();
    this->gui.reset();
    this->getNetworkManager().stop();
}
