/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** client manager
*/

#include "ClientManager.hpp"

#include <graphical_library/raylib/Raylib.hpp>

#include "client/state_machine/states/connecting/Connecting.hpp"

/*#include "client/states/game/InGameState.hpp"
#include "client/states/lobby/LobbyState.hpp"
#include "client/states/connecting/ConnectingState.hpp"*/

#include <iostream>
#include <network/logger/Logger.hpp>

#include <cstdlib>
#include <memory>


ClientManager::ClientManager()
    : stateMachine(std::make_unique<Connecting>(*this, this->registry))
{
    this->gui = std::make_unique<Raylib>();

    this->gui->init();
    /*
    this->_gameStateFactory[AUTHENTIFICATION] = [this] {
        return std::make_unique<ConnectingState>(*this);
    };
    this->_gameStateFactory[LOBBY] = [this] {
        return std::make_unique<LobbyState>(*this);
    };
    this->_gameStateFactory[IN_GAME] = [this] {
        return std::make_unique<InGameState>(*this);
    };
    */
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
