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
#include <atomic>
#include <memory>
#include <mutex>
#include <unordered_map>

class Game
{
  public:
    Game(class Server &server);
    ~Game() = default;
    void start();
    void stop();
    void loop(int ticks);
    std::pair<std::size_t, std::size_t> addPlayer();
    void RemovePlayer(std::size_t id);
    Registry &getRegistry();
    std::mutex &getRegistryMutex();
    EntityFactory &getFactory();
    GameBoss &getGameBoss();
    std::unordered_map<std::size_t, std::size_t> &getPlayers();
    void sendPackets(std::shared_ptr<Packet> packet);
    bool isRunning() const;

  private:
    void initializeComponents();
    void initializeSystems();

    Registry _registry;
    EntityFactory _factory;
    std::atomic<bool> _isRunning;
    class Server &_server;
    GameBoss _gameBoss;
    std::unordered_map<std::size_t, std::size_t> _players;
    std::mutex _registryMutex;
};

#endif /* GAME_HPP */
