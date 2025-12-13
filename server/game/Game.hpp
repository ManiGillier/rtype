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
#include "../packet_queue/PacketQueue.hpp"

class Game {
public:
    Game();
    ~Game() = default;
    void start();
    void update();
    Entity addPlayer(std::shared_ptr<Player> &player);
    void removePlayer(std::shared_ptr<Player> &player);
    Entity addBodss();
    Registry& getRegistry();
    PacketQueue& getPacketQueue();

private:
    void initializeComponents();
    void initializeSystems();

    Registry _registry;
    EntityFactory _factory;
    PacketQueue _packets;
    std::unordered_map<int, Entity> _players;
    bool _isRunning;
};

#endif /* GAME_HPP */
