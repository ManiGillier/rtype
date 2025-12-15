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
    Game();
    ~Game() = default;
    void start();
    void loop(int ticks);
    std::pair<Entity, Entity> addPlayer();
    Registry& getRegistry();
    std::mutex& getRegistryMutex();
    void sendAllPackets(class Server& server);
    void addPacketToSend(std::shared_ptr<Packet> packet);

private:
    void initializeComponents();
    void initializeSystems();

    Registry _registry;
    EntityFactory _factory;
    std::vector<std::shared_ptr<Packet>> _packet_to_send;
    bool _isRunning;
    std::mutex _registryMutex;
};

#endif /* GAME_HPP */
