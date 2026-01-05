/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** game
*/

#ifndef GAME_HPP
#define GAME_HPP

#include "../player/Player.hpp"
#include "ecs/regisrty/Registry.hpp"
#include "../game/factories/EntityFactory.hpp"
#include <memory>
#include <vector>

class Game
{
  public:
    Game();
    ~Game() = default;
    void loop(int ticks);
    void addPlayer(std::shared_ptr<Player> &player);
    void removePlayer(std::shared_ptr<Player> &player);

  private:
    /*
       init helpers to creates players entity then send entity Id to the client
    */
    void initPlayers();
    void initializeComponents();
    void initializeSystems();
    /*
       players set by LobbyManager they need their own method
       because when player deconnect he needs to be removed from current game by
       killing his entity
    */
    std::mutex _playersMutex;
    std::vector<std::pair<std::shared_ptr<Player>, std::size_t>> _players;
    /*
       Registry and Entity factory
    */
    Registry _registry;
    EntityFactory _factory;
    std::mutex _registryMutex;
    bool _isRunning;
};

#endif /* GAME_HPP */
