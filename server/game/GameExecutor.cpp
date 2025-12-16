#include "GameExecutor.hpp"
#include "../RTypeServer.hpp"
#include "network/logger/Logger.hpp"
#include "network/packets/impl/StartGamePacket.hpp"

GameExecutor::GameExecutor(RTypeServer &server)
    : _rtypeServer(server), _hasStarted(false)
{
}

bool GameExecutor::execute(Server &server, std::shared_ptr<Player> player,
                           std::shared_ptr<StartGamePacket> packet)
{
    (void)server;
    (void)player;
    (void)packet;

    // TODO: check for several player
    if (_hasStarted) {
        LOG("Game already started");
        return false;
    }
    _hasStarted = true;
    return true;
}
