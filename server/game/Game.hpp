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
#include "../../network/packets/Packet.hpp"
#include <memory>
#include <vector>
#include <mutex>

class Game {
public:
    Game(class Server &server);
    ~Game() = default;
    void start();
    void loop(int ticks);
    std::pair<Entity, Entity> addPlayer();
    Registry& getRegistry();
    std::mutex& getRegistryMutex();
    void sendPackets(std::shared_ptr<Packet> packet);

private:
    void initializeComponents();
    void initializeSystems();

    Registry _registry;
    EntityFactory _factory;
    bool _isRunning;
    class Server &_server;
    std::mutex _registryMutex;
};

#endif /* GAME_HPP */
