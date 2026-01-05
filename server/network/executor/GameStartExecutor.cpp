#include "GameStartExecutor.hpp"
#include "../../network/server/RTypeServer.hpp"
#include "network/logger/Logger.hpp"
#include "network/packets/impl/StartGamePacket.hpp"
#include "server/lobby/LobbyManager.hpp"
#include <memory>

GameStartExecutor::GameStartExecutor(RTypeServer &server)
    : _rtypeServer(server), _hasStarted(false)
{
}

bool GameStartExecutor::execute(Server &server, std::shared_ptr<Player> player,
                                std::shared_ptr<StartGamePacket> packet)
{
    (void)packet;
    (void)server;

    LOG("Game start request recivied from " << player->getId());

    auto lobbyId = player->getLobbyId();
    auto lobby = this->_rtypeServer.getLobbyManager().getLobbies()[lobbyId];

    if (!lobby->isInGame()) {
        auto startPacket = create_packet(StartGamePacket);

        for (auto &player : lobby->getPlayers())
            player->sendPacket(startPacket);
        /*
           Set this lobby to game mode to not start multiple game at same time:
           in case of different player on the same lobby press start at the same
           time.
        */
        LOG("Game has started from lobby " << lobbyId);
        lobby->setIsInGame(true);

        auto lobbyManager = this->_rtypeServer.getLobbyManager();

        this->_rtypeServer.getGameThreadPool().push_task(
            &LobbyManager::startGame, lobbyManager, lobbyId);
    }
    return true;
}
