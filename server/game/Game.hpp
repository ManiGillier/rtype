/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** game
*/

#ifndef GAME_HPP
#define GAME_HPP

#include "../game/factories/EntityFactory.hpp"
#include "../network/network_manager/NetworkManager.hpp"
#include "../player/Player.hpp"
#include "ecs/regisrty/Registry.hpp"
#include "server/game/ticker/Ticker.hpp"
#include <cstdint>
#include <memory>

class Game
{
  public:
    Game(std::vector<std::shared_ptr<Player>> &players,
         std::mutex &playersMutex);
    ~Game() = default;
    void loop(int ticks);
    NetworkManager &getNetworkManager();
    std::tuple<std::mutex &, Registry &> getRegistry();
    bool isRunning();

  private:
    void sendCurrentTime(Ticker &ticker);
    void setDiffTime();
    /*
       init helpers to creates players entity then send entity Id to the client
    */
    void initPlayers();
    void initializeComponents();
    void initializeSystems();
    /*
       reset helpers to reset entities when game has finished
    */
    void resetPlayersEntities();
    /*
       players set by LobbyManager they need their own method
       because when player deconnect he needs to be removed from current game by
       killing his entity
    */
    std::mutex &_playersMutex;
    std::vector<std::shared_ptr<Player>> &_players;
    NetworkManager _networkManager;
    /*
       Registry and Entity factory
    */
    std::mutex _registryMutex;
    Registry _registry;
    EntityFactory _factory;

    std::mutex _runningMutex;
    std::chrono::steady_clock::time_point _gameStart;
    std::chrono::steady_clock::time_point _lastTick;
    bool _isRunning;
};

#endif /* GAME_HPP */
