/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** client manager
*/

#include "ClientManager.hpp"
#include "client/raylib/Raylib.hpp"

#include "client/states/game/InGameState.hpp"
#include "client/states/lobby/LobbyState.hpp"

#include <network/logger/Logger.hpp>

#include <cstdlib>
#include <memory>

ClientManager::ClientManager()
{
    this->gui = std::make_unique<Raylib>(*this);

    this->_gameStateFactory[LOBBY] = [this] {
        return std::make_unique<LobbyState>(*this);
    };
    this->_gameStateFactory[IN_GAME] = [this] {
        return std::make_unique<InGameState>(*this);
    };
}

inline auto ClientManager::changeInternalState(std::unique_ptr<IGameState> state)
-> void
{
    this->_internal_state = std::move(state);
}

auto ClientManager::changeState(const State state) -> void
{
    this->networkManager->resetExecutors();
    this->changeInternalState(this->_gameStateFactory[state]());
    this->_state = state;
}

auto ClientManager::launch(int argc, char **argv) -> void
{
    if (argc != 3 && argc != 4)
        return;
    if (argc == 4 && std::string(argv[5]) == "-d")
        Logger::shouldLog = true;
    this->networkManager =
        std::make_unique<NetworkManager>(argv[1], std::atoi(argv[2]));

    this->changeState(LOBBY);
    this->loop();
}

auto ClientManager::loop() -> void
{
    while (true) {
        this->getGui().render(this->getState());
        if (this->getGui().isStopped())
            break;
        this->networkManager->getClient().executePackets();
        State new_state = this->getState().update();

        if (new_state == State::END_STATE)
            break;
        if (new_state != State::NONE)
            this->changeState(new_state);
    }
    this->unload();
}

auto ClientManager::unload() -> void
{
    this->_internal_state.reset();
    this->_state = END_STATE;
    this->gui.reset();
    this->getNetworkManager().stop();
}
