/*
** EPITECH PROJECT, 2026
** rtype [WSL: Ubuntu-24.04]
** File description:
** RCONRequestExecutor
*/

#include "RCONRequestExecutor.hpp"
#include "../server/RTypeServer.hpp"
#include <network/packets/Packet.hpp>
#include <network/packets/impl/RCONResponse.hpp>

RCONRequestExecutor::RCONRequestExecutor(RTypeServer &server) : _rtypeServer(server) {}

bool RCONRequestExecutor::execute(Server &server,
                                  std::shared_ptr<Player> player,
                                  std::shared_ptr<RCONRequest> packet)
{
    const std::string &rconKey = _rtypeServer.getRTypeConfig().getKey();
    const std::string &packetKey = packet->getSpecifiedKey();

    (void) server;
    if (rconKey != packetKey) {
        std::shared_ptr<RCONResponse> rsp = std::make_shared<RCONResponse>();
        player->sendPacket(rsp);
        return true;
    }
    switch (packet->getRequestType()) {
        case RCONRequest::LIST:
            list(player);
            break;
        case RCONRequest::KICK:
            kick(player, packet->getTarget());
            break;
        case RCONRequest::BAN:
            ban(player, packet->getTarget());
            break;
        default:
            break;
    }
    return true;
}

void RCONRequestExecutor::kick(std::shared_ptr<Player> player, const std::string &target)
{
    std::shared_ptr<Player> p = _rtypeServer.getPlayerByUsername(target);
    std::shared_ptr<RCONResponse> rsp = std::make_shared<RCONResponse>();

    rsp->clearResponses();
    if (!p) {
        rsp->addResponse(NO_SUCH_PLAYER_ONLINE + target + ".");
    } else {
        _rtypeServer.disconnectClient(p);
        rsp->addResponse(SUCCESSFULLY_KICKED + target + ".");
    }
    player->sendPacket(rsp);
}

void RCONRequestExecutor::ban(std::shared_ptr<Player> player, const std::string &target)
{
    (void) player;
    (void) target;
    return;
}

void RCONRequestExecutor::list(std::shared_ptr<Player> player)
{
    std::vector<std::shared_ptr<IPollable>> pollables =
        _rtypeServer.getPollManager().getPool();
    std::shared_ptr<RCONResponse> rsp = std::make_shared<RCONResponse>();
    
    rsp->clearResponses();
    rsp->addResponse(HERE_IS_THE_LIST_OF_PLAYERS);
    for (std::shared_ptr<IPollable> &p : pollables) {
        std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(p);
        if (!player || (player && !player->isConnected()) ||
            (player && player->getUsername().empty()))
            continue;
        rsp->addResponse("- " + player->getUsername());
    }
    player->sendPacket(rsp);
}
