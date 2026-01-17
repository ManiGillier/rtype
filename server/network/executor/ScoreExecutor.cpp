/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** ScoreExecutor
*/

#include <network/logger/Logger.hpp>
#include <network/packets/impl/LoginResponse.hpp>
#include "../../database/AccountDatabase.hpp"
#include "../server/RTypeServer.hpp"
#include "ScoreExecutor.hpp"

ScoreExecutor::ScoreExecutor(RTypeServer &server) : _rtypeServer(server) {}

bool ScoreExecutor::execute(Server &server, std::shared_ptr<Player> player,
                               std::shared_ptr<ScorePacket> packet)
{
    (void) server;
    if (packet->getRequest() == ScorePacket::REQUEST) {
        try {
            std::shared_ptr<ScorePacket> sp =
                create_packet(ScorePacket, ScorePacket::LIST);
            AccountDatabase &db = _rtypeServer.getAccountDatabase();
            std::vector<std::string> usernames = db.getScoreboard();

            for (const std::string &username : usernames)
                sp->addUsername(username);
            player->sendPacket(sp);
        } catch (const AccountDatabase::DatabaseError &e) {
            return true;
        }
    }
    return true;
}
