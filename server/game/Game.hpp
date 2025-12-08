/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** game
*/

#ifndef GAME_HPP
#define GAME_HPP

#include "../../ecs/regisrty/Registry.hpp"
#include "../factories/EntityFactory.hpp"
#include <map>

class Game {
public:
    Game();
    ~Game() = default;
    void start();
    void update();
    Entity addPlayer(/* Player *player (client abstraction) */);
    void removePlayer(/* Player *player (client abstraction) */);
    Registry& getRegistry();

private:
    void initializeComponents();
    void initializeSystems();

    Registry _registry;
    EntityFactory _factory;
    std::map<int, Entity> _players;
    std::optional<Entity> _currentBoss;
    bool _isRunning;
};

#endif /* GAME_HPP */
