#include "Game.hpp"
#include "components/Acceleration.hpp"
#include "components/Damager.hpp"
#include "components/Healer.hpp"
#include "components/Hitable.hpp"
#include "components/OutsideBoundaries.hpp"
#include "components/Pattern.hpp"
#include "components/Resistance.hpp"
#include "components/Tag.hpp"
#include "components/Velocity.hpp"
#include "ecs/regisrty/Registry.hpp"
#include "gameplay/GamePlay.hpp"
#include "network/packets/Packet.hpp"
#include "shared/components/Dependence.hpp"
#include "shared/components/Health.hpp"
#include "shared/components/HitBox.hpp"
#include "shared/components/Laser.hpp"
#include "shared/components/Position.hpp"
#include "systems/GameSystems.hpp"
#include "ticker/Ticker.hpp"
#include <chrono>
#include <cstdint>
#include <functional>
#include <memory>
#include <mutex>
#include <network/packets/impl/GameOverPacket.hpp>
#include <network/packets/impl/HitboxSizeUpdatePacket.hpp>
#include <network/packets/impl/NewPlayerPacket.hpp>
#include <network/packets/impl/TimeNowPacket.hpp>
#include <optional>
#include <thread>
#include <tuple>

Game::Game(std::vector<std::shared_ptr<Player>> &players,
           std::mutex &playersMutex)
    : _playersMutex(playersMutex), _players(players),
      _networkManager(playersMutex, _players), _factory(this->_registry),
      _isRunning(false)
{
}

void Game::loop(int ticks)
{
    Ticker ticker(ticks);
    GamePlay gamePlay(this->_networkManager, this->_registry, this->_factory);
    this->_gameStart = std::chrono::steady_clock::now();

    this->_isRunning = true;
    std::this_thread::sleep_for(
        std::chrono::milliseconds(200)); // TODO: remove this

    this->initializeComponents();
    this->initializeSystems();
    this->initPlayers();

    bool running = true;

    do {
        this->sendCurrentTime(ticker);
        this->_networkManager.flush();
        {
            std::lock_guard<std::mutex> lock(_registryMutex);
            _registry.update();
            if (gamePlay.update()) {
                std::lock_guard<std::mutex> lock(_runningMutex);
                _isRunning = false;
                break;
            }
        }
        {
            std::lock_guard<std::mutex> lock(_runningMutex);
            running = _isRunning;
        }
        ticker.wait();
    } while (running);

    this->_networkManager.flush();
    this->_networkManager.clear();
    this->resetPlayersEntities();
    this->_registry = Registry();
}

void Game::sendCurrentTime(Ticker &ticker)
{
    auto now = ticker.now() - _gameStart;
    auto time_ms = static_cast<uint32_t>(
        std::chrono::duration_cast<std::chrono::milliseconds>(now).count());
    _networkManager.queuePacket(create_packet(TimeNowPacket, time_ms));
}

void Game::initPlayers()
{
    std::vector<std::pair<std::size_t, std::size_t>> playerData;
    {
        std::lock_guard<std::mutex> lockPlayers(_playersMutex);
        for (auto &pl : _players) {
            {
                std::lock_guard<std::mutex> lockRegistry(_registryMutex);
                Entity player = _factory.createPlayer();
                Entity laser = _factory.createPlayerLaser(
                    static_cast<int>(player.getId()));
                pl->setEntityId(player.getId());
                playerData.push_back(
                    std::make_pair(player.getId(), laser.getId()));
            }
        }
    }
    for (const auto &[playerId, laserId] : playerData) {
        auto newPlayerPacket =
            create_packet(NewPlayerPacket, playerId, laserId);

        auto hitBox = _registry.get<HitBox>(playerId);
        std::shared_ptr<Packet> HitBoxSize = nullptr;
        if (hitBox.has_value()) {
            HitBoxSize = create_packet(HitboxSizeUpdatePacket, playerId,
                                       hitBox->width, hitBox->height);
        }
        _networkManager.queuePacket(HitBoxSize);
        _networkManager.queuePacket(newPlayerPacket);
    }
}

void Game::initializeComponents()
{
    _registry.register_component<Acceleration>();
    _registry.register_component<Damager>();
    _registry.register_component<Resistance>();
    _registry.register_component<Velocity>();
    _registry.register_component<Dependence>();
    _registry.register_component<OutsideBoundaries>();
    _registry.register_component<Health>();
    _registry.register_component<HitBox>();
    _registry.register_component<Laser>();
    _registry.register_component<Position>();
    _registry.register_component<Pattern>();
    _registry.register_component<Tag>();
    _registry.register_component<Healer>();
    _registry.register_component<Hitable>();
}

void Game::initializeSystems()
{
    _registry
        .add_update_system<Position, Velocity, Acceleration, OutsideBoundaries>(
            Systems::position_system, std::ref(_networkManager));
    _registry.add_update_system<Position, Acceleration, Pattern>(
        Systems::pattern_system, std::ref(_networkManager));
    _registry.add_update_system<Position, Laser>(Systems::update_laser_system,
                                                 std::ref(_networkManager));
    _registry.add_update_system<Position, HitBox>(Systems::collision_system,
                                                  std::ref(_networkManager));
    _registry.add_update_system<Health>(Systems::health_system,
                                        std::ref(_networkManager));
    _registry.add_update_system<Tag>(
        Systems::loose_system, std::ref(_networkManager),
        std::ref(_runningMutex), std::ref(_isRunning));
}

void Game::resetPlayersEntities()
{
    std::lock_guard<std::mutex> lock(_playersMutex);
    for (auto &it : _players)
        it->setEntityId(std::nullopt);
}

std::tuple<std::mutex &, Registry &> Game::getRegistry()
{
    return std::tie(this->_registryMutex, this->_registry);
}

NetworkManager &Game::getNetworkManager()
{
    return this->_networkManager;
}

bool Game::isRunning()
{
    std::lock_guard<std::mutex> lock(_runningMutex);
    return _isRunning;
}
