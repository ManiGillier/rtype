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
#include <network/packets/impl/SetAdminPacket.hpp>

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
        case RCONRequest::UNBAN:
            unban(player, packet->getTarget());
            break;
        case RCONRequest::BANLIST:
            banlist(player);
            break;
        case RCONRequest::SETADMIN:
            setAdmin(player, packet->getTarget());
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
    AccountDatabase &db = _rtypeServer.getAccountDatabase();
    std::shared_ptr<RCONResponse> rsp = std::make_shared<RCONResponse>();

    rsp->clearResponses();
    try {
        if (!db.hasUsername(target)) {
            rsp->addResponse(NO_SUCH_PLAYER_REGISTERED + target + ".");
        } else if (db.isBanned(target)) {
            rsp->addResponse(PLAYER_IS_ALREADY_BANNED + target + ".");
        } else {
            db.setBanned(target, true);
            std::shared_ptr<Player> p = _rtypeServer.getPlayerByUsername(target);
            if (p)
                _rtypeServer.disconnectClient(p);
            rsp->addResponse(SUCCESSFULLY_BANNED + target + ".");
        }
    } catch (const AccountDatabase::DatabaseError &e) {
        rsp->addResponse(e.what());
    }
    player->sendPacket(rsp);
}

void RCONRequestExecutor::unban(std::shared_ptr<Player> player,
                                const std::string &target)
{
    AccountDatabase &db = _rtypeServer.getAccountDatabase();
    std::shared_ptr<RCONResponse> rsp = std::make_shared<RCONResponse>();
    
    rsp->clearResponses();
    try {
        if (!db.hasUsername(target)) {
            rsp->addResponse(NO_SUCH_PLAYER_REGISTERED + target + ".");
        } else if (db.isBanned(target)) {
            db.setBanned(target, false);
            rsp->addResponse(SUCCESSFULLY_UNBANNED + target + ".");
        } else {
            rsp->addResponse(PLAYER_IS_NOT_BANNED + target + ".");
        }
    } catch (const AccountDatabase::DatabaseError &e) {
        rsp->addResponse(e.what());
    }
    player->sendPacket(rsp);
}

void RCONRequestExecutor::setAdmin(std::shared_ptr<Player> player,
                                   const std::string &target)
{
    std::shared_ptr<Player> p = _rtypeServer.getPlayerByUsername(target);
    std::shared_ptr<RCONResponse> rsp = std::make_shared<RCONResponse>();

    rsp->clearResponses();
    if (!p) {
        rsp->addResponse(NO_SUCH_PLAYER_ONLINE + target + ".");
    } else {
        p->sendPacket(create_packet(SetAdminPacket));
        rsp->addResponse(SUCCESSFULLY_MADE_ADMIN + target + ".");
    }
    player->sendPacket(rsp);
}

void RCONRequestExecutor::banlist(std::shared_ptr<Player> player)
{
    std::vector<std::shared_ptr<IPollable>> pollables =
        _rtypeServer.getPollManager().getPool();
    std::shared_ptr<RCONResponse> rsp = std::make_shared<RCONResponse>();

    rsp->clearResponses();
    rsp->addResponse(HERE_IS_THE_BANLIST);
    try {
        std::vector<std::string> bannedUsers = _rtypeServer.getAccountDatabase().
            getAllBans();
        for (const std::string &bannedUser : bannedUsers) {
            rsp->addResponse("- " + bannedUser);
        }
    } catch (const AccountDatabase::DatabaseError &e) {
        rsp->addResponse(e.what());
    }
    player->sendPacket(rsp);
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
