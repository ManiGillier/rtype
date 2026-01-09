#include "GameStartExecutor.hpp"
#include "../../network/server/RTypeServer.hpp"
#include "network/logger/Logger.hpp"
#include "network/packets/impl/StartGamePacket.hpp"
#include "server/lobby/LobbyManager.hpp"
#include <memory>
#include <mutex>

GameStartExecutor::GameStartExecutor(RTypeServer &server)
    : _rtypeServer(server)
{
}

bool GameStartExecutor::execute(Server &server, std::shared_ptr<Player> player,
                                std::shared_ptr<StartGamePacket> packet)
{
    (void)packet;
    (void)server;

    LOG("Game start request recivied from " << player->getId());

    auto lobbyId = player->getLobbyId();
    auto lobby = this->_rtypeServer.getLobbyManager().getLobby(lobbyId);

    if (!lobby) {
        LOG("Eror: Lobby " << lobbyId << " not found");
        return true;
    }

    if (!lobby->isInGame()) {
        std::vector<std::shared_ptr<Player>> playersCopy;
        {
            std::lock_guard<std::mutex> lock(lobby->getPlayersMutex());
            playersCopy = lobby->getPlayers();
        }
        auto startPacket = create_packet(StartGamePacket);

        for (auto &player : playersCopy)
            player->sendPacket(startPacket);
        /*
           Set this lobby to game mode to not start multiple game at same time:
           in case of different player on the same lobby press start at the same
           time.
        */
        LOG("Game has started from lobby " << lobbyId);
        lobby->setIsInGame(true);

        auto *lobbyManagerPtr = &this->_rtypeServer.getLobbyManager();
        this->_rtypeServer.getGameThreadPool().push_task(
            &LobbyManager::startGame, lobbyManagerPtr, lobbyId);
    }
    return true;
}
