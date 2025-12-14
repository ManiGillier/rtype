#include "GameExecutor.hpp"
#include "../RTypeServer.hpp"
#include "Game.hpp"
#include "network/logger/Logger.hpp"
#include <chrono>
#include <thread>

GameExecutor::GameExecutor(RTypeServer &server)
    : _rtypeServer(server), _hasStarted(false), _isRunning(false)
{
}

GameExecutor::~GameExecutor()
{
    stop();
    join();
}

void GameExecutor::stop()
{
    _isRunning = false;
}

void GameExecutor::join()
{
    if (_gameThread.joinable()) {
        _gameThread.join();
    }
}

bool GameExecutor::isRunning() const
{
    return _isRunning;
}

bool GameExecutor::execute(Server &server, std::shared_ptr<Player> &player,
                           std::shared_ptr<StartRequestPacket> packet)
{
    (void)server;
    (void)player;
    (void)packet;

    // TODO: check for several player
    if (_hasStarted) {
        LOG("Game already started");
        return false;
    }

    LOG("Starting game");
    _rtypeServer.getGame().start();
    _isRunning = true;
    _hasStarted = true;
    _gameThread = std::thread(&GameExecutor::gameLoop, this);
    return true;
}

void GameExecutor::gameLoop()
{
    Game &game = _rtypeServer.getGame();
    int ticks = _rtypeServer.getTicks();
    auto tickDuration = std::chrono::milliseconds(1000 / ticks);

    LOG("Game loop started with: " << ticks << " ticks per second");

    while (_isRunning) {
        auto startTime = std::chrono::steady_clock::now();

        std::vector<std::shared_ptr<Packet>> receivedPackets;
        for (auto& pollable : _rtypeServer.getPollManager().getPool()) {
            auto& packetQueue = pollable->getReceivedPackets();
            while (!packetQueue.empty()) {
                receivedPackets.push_back(packetQueue.front());
                packetQueue.pop();
            }
        }
        game.update(receivedPackets);

        auto endTime = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            endTime - startTime);
        auto sleepTime = tickDuration - elapsed;
        if (sleepTime.count() > 0) {
            std::this_thread::sleep_for(sleepTime);
        }
    }
    LOG("Game loop stopped");
}
