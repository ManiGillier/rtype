#include "GameExecutor.hpp"
#include <thread>
#include "Game.hpp"
#include "network/logger/Logger.hpp"

// GameExecutor::GameExecutor(RtypeServer &rtype) : _rtype(rtype)
// {
//     return;
// }

bool GameExecutor::execute(Server &server, std::shared_ptr<Player> &player,
                           std::shared_ptr<GameStartPacketRequest> packet)
{
    (void)server;
    (void)player;
    (void)packet;
    LOG("caca");
    // if (_hasStarted)
    //     return false;
    // std::thread gameThread = /* Commence un thread de jeu ici */
    //
    //     this->_rtype.addThread(gameThread);
    //
    // /* Un jeu a été commencé ! :O */
    // _hasStarted = true;
    return true;
}
