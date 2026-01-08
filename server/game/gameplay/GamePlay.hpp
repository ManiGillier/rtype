/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** game
*/

#ifndef GAMEPLAY_HPP
#define GAMEPLAY_HPP

#include "ecs/entity/Entity.hpp"
#include "ecs/regisrty/Registry.hpp"
#include "server/network/network_manager/NetworkManager.hpp"
#include <chrono>

class Game;

enum GameState { waiting = 0, active, completed };

class GamePlay
{
  public:
    GamePlay(NetworkManager &nm, Registry &r);
    ~GamePlay() = default;
    void update();

  private:
    NetworkManager &_networkManager;
    Registry &_regisrty;
    std::chrono::steady_clock::time_point _start;
    GameState _state;
    void spawnBoss();
};

#endif /* GAMEPLAY_HPP */
