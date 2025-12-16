#include "GameExecutor.hpp"
#include "../RTypeServer.hpp"
#include "network/logger/Logger.hpp"
#include "network/packets/impl/StartGamePacket.hpp"
#include <memory>

GameExecutor::GameExecutor(RTypeServer &server)
    : _rtypeServer(server), _hasStarted(false)
{
}

bool GameExecutor::execute(Server &server, std::shared_ptr<Player> player,
                           std::shared_ptr<StartGamePacket> packet)
{
    (void)player;
    (void)packet;

    if (_hasStarted) {
        LOG("Game already started");
        return false;
    }
    auto &pool = server.getPollManager().getPool();
    if (pool.size() < 2 || pool.size() > 10) {
        LOG("Can't to start game (need at least 2 and max 10, got "
            << pool.size() << ")");
        return false;
    }
    _hasStarted = true;
    _rtypeServer.setStart();

    auto startPacket = create_packet(StartGamePacket);
    for (auto &pollable : server.getPollManager().getPool())
        pollable->sendPacket(startPacket);
    return true;
}
