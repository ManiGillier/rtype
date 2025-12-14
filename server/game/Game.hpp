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
#include "../../network/packets/Packet.hpp"
#include <memory>
#include <vector>

class Game {
public:
    Game();
    ~Game() = default;
    void start();
    void update(std::vector<std::shared_ptr<Packet>>& receivedPackets);
    Entity addPlayer(std::shared_ptr<Player> &player);
    void removePlayer(std::shared_ptr<Player> &player);
    Entity addBodss();
    Registry& getRegistry();

private:
    void initializeComponents();
    void initializeSystems();

    Registry _registry;
    EntityFactory _factory;
    std::unordered_map<int, Entity> _players;
    bool _isRunning;
};

#endif /* GAME_HPP */
