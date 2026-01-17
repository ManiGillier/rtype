#include "TextChatStringExecutor.hpp"
#include "../server/RTypeServer.hpp"
#include <network/packets/impl/TextChatStringPacket.hpp>

bool TextChatStringExecutor::execute(
    Server &server, std::shared_ptr<Player> player,
    std::shared_ptr<TextChatStringPacket> packet)
{
    (void)server;

    LOG("Get chat string from" << player->getId());

    auto lobbyId = player->getLobbyId();
    auto lobby = this->_rtypeServer.getLobbyManager().getLobby(lobbyId);
    std::string textToSend;

    if (!lobby) {
        LOG("Eror: Lobby " << lobbyId << " not found");
        return true;
    }

    std::vector<std::shared_ptr<Player>> playersCopy;
    {
        std::lock_guard<std::mutex> lock(lobby->getPlayersMutex());
        playersCopy = lobby->getPlayers();
    }

    textToSend = player->getUsername() + ": " + packet->getStr();
    auto textToSendPacket = create_packet(TextChatStringPacket, textToSend);

    for (auto &player : playersCopy)
        player->sendPacket(textToSendPacket);

    LOG("send string: " << textToSend << " to all player from " << lobbyId);
    return true;
}
