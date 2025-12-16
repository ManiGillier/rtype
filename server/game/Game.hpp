/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** game
*/

#ifndef GAME_HPP
#define GAME_HPP

#include "../../ecs/regisrty/Registry.hpp"
#include "../../network/packets/Packet.hpp"
#include "../factories/EntityFactory.hpp"
#include "ecs/entity/Entity.hpp"
#include "GameBoss.hpp"
#include <memory>
#include <mutex>
#include <unordered_map>

class Game
{
  public:
    Game(class Server &server);
    ~Game() = default;
    void start();
    void loop(int ticks);
    std::pair<Entity, Entity> addPlayer();
    Registry &getRegistry();
    std::mutex &getRegistryMutex();
    EntityFactory &getFactory();
    void sendPackets(std::shared_ptr<Packet> packet);

  private:
    void initializeComponents();
    void initializeSystems();

    Registry _registry;
    EntityFactory _factory;
    bool _isRunning;
    class Server &_server;
    GameBoss _gameBoss;
    std::unordered_map<std::size_t, std::size_t> _players;
    std::mutex _registryMutex;
};

#endif /* GAME_HPP */
