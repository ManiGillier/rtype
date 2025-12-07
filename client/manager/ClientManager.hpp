/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** manages the client
*/

#ifndef CLIENT_MANAGER_HPP
#define CLIENT_MANAGER_HPP

#include "client/GameInterface.hpp"
#include "client/GraphicalLibInterface.hpp"

#include "ecs/regisrty/Registry.hpp"

#include "client/api/IGameState.hpp"

#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

class ClientManager
{
public:
    enum State {
        NONE = 0,
        IN_GAME,
    };
    ClientManager();
    ~ClientManager();
    auto changeState(const State) -> void;
private:
    auto changeInternalState(std::unique_ptr<IGameState>) -> void;
private:
    std::unique_ptr<GraphicalLibAPI> gui = nullptr;
    std::unique_ptr<GameLogicAPI> game = nullptr;

    State _state = NONE;
    std::unique_ptr<IGameState> _internal_state = nullptr;

    std::unordered_map<State, std::function<std::unique_ptr<IGameState>()>>
        _gameStateFactory;
};

#endif /* CLIENT_MANAGER_HPP */
