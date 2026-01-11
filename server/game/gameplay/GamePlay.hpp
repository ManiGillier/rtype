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
#include "../factories/EntityFactory.hpp"
#include "Boss.hpp"
#include <chrono>
#include <memory>
#include <vector>

enum GameState { waiting = 0, active, completed };

class GamePlay
{
  public:
    GamePlay(NetworkManager &nm, Registry &r, EntityFactory &factory);
    ~GamePlay() = default;
    void update();

  private:
    void spawnBoss();
    void removeDeadBoss();
    NetworkManager &_networkManager;
    Registry &_regisrty;
    EntityFactory &_factory;

    // gamePlay fields
    std::chrono::steady_clock::time_point _start;
    GameState _state;

    std::vector<std::unique_ptr<Boss>> _bosses;
};

#endif /* GAMEPLAY_HPP */
