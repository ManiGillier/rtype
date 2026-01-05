/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** manages the client
*/

#ifndef CLIENT_MANAGER_HPP
#define CLIENT_MANAGER_HPP

#include "client/states/State.hpp"

#include "ecs/regisrty/Registry.hpp"

#include "client/api/IGameState.hpp"

#include <graphical_library/api/GraphicalLibrary.hpp>

#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

#include <network/client/Client.hpp>

#include "NetworkManager.hpp"

class ClientManager
{
public:
    ClientManager();
    auto changeState(const State) -> void;

    auto getGui() -> gl::GraphicalLibrary & { return *this->gui; }
    auto getState() -> IGameState & { return *this->_internal_state; }
    auto getNetworkManager() -> NetworkManager &
        { return *this->networkManager; }
    auto launch(int argc, char **argv) -> void;
private:
    auto changeInternalState(std::unique_ptr<IGameState>) -> void;
    auto loop() -> void;
    auto unload() -> void;
private:
    std::unique_ptr<gl::GraphicalLibrary> gui;
    std::unique_ptr<NetworkManager> networkManager;

    State _state = NONE;
    std::unique_ptr<IGameState> _internal_state = nullptr;

    std::unordered_map<State, std::function<std::unique_ptr<IGameState>()>>
        _gameStateFactory;
};

#endif /* CLIENT_MANAGER_HPP */
