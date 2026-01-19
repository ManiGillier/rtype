#include "LobbyConfigExecutor.hpp"
#include "../../network/server/RTypeServer.hpp"
#include "network/logger/Logger.hpp"
#include "network/packets/impl/LobbyConfigPacket.hpp"
#include "server/lobby/LobbyManager.hpp"
#include <memory>
#include <mutex>

LobbyConfigExecutor::LobbyConfigExecutor(RTypeServer &server) : _rtypeServer(server)
{
}

bool LobbyConfigExecutor::execute(Server &server, std::shared_ptr<Player> player,
                                std::shared_ptr<LobbyConfigPacket> packet)
{
    (void)packet;
    (void)server;

    auto lobbyId = player->getLobbyId();
    auto lobby = this->_rtypeServer.getLobbyManager().getLobby(lobbyId);

    if (!lobby) {
        LOG("Eror: Lobby " << lobbyId << " not found");
        return true;
    }

    if (!lobby->isInGame()) {
        std::vector<std::shared_ptr<Player>> playersCopy;
        std::lock_guard<std::mutex> lock(lobby->getPlayersMutex());
        playersCopy = lobby->getPlayers();
        auto config = packet->getConfig();
        auto configPacket = create_packet(LobbyConfigPacket, config);

        for (auto &player : playersCopy)
            player->sendPacket(configPacket);
    }
    return true;
}
