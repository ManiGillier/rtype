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
#include "../player/Player.hpp"

class Game {
public:
    Game();
    ~Game() = default;
    void start();
    void update();
    Entity addPlayer(const std::unique_ptr<Player> &player /* Player *player (client abstraction) */);
    void removePlayer(const std::unique_ptr<Player> &player /* Player *player (client abstraction) */);
    Registry& getRegistry();

private:
    void initializeComponents();
    void initializeSystems();

    Registry _registry;
    EntityFactory _factory;
    std::unordered_map<int, Entity> _players;
    std::optional<Entity> _currentBoss;
    bool _isRunning;
};

#endif /* GAME_HPP */
