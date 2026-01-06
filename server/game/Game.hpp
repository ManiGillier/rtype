/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** game
*/

#ifndef GAME_HPP
#define GAME_HPP

#include "../game/factories/EntityFactory.hpp"
#include "../player/Player.hpp"
#include "ecs/regisrty/Registry.hpp"
#include <memory>
#include <vector>

class Game
{
  public:
    Game(std::mutex &playersMutex);
    ~Game() = default;
    void loop(int ticks);
    void addPlayer(std::shared_ptr<Player> &player);
    void removePlayer(std::shared_ptr<Player> &player);
    void sendPackets(std::shared_ptr<Packet> packet);
    std::tuple<std::mutex &, Registry &> getRegistry();

  private:
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
    std::vector<std::shared_ptr<Player>> _players;
    /*
       Registry and Entity factory
    */
    std::mutex _registryMutex;
    Registry _registry;
    EntityFactory _factory;
    bool _isRunning;
};

#endif /* GAME_HPP */
