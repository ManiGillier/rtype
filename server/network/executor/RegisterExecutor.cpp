/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** RegisterExecutor
*/

#include <network/logger/Logger.hpp>
#include <network/packets/impl/LoginResponse.hpp>
#include "../../database/AccountDatabase.hpp"
#include "../server/RTypeServer.hpp"
#include "RegisterExecutor.hpp"

RegisterExecutor::RegisterExecutor(RTypeServer &server) : _rtypeServer(server) {}

bool RegisterExecutor::execute(Server &server, std::shared_ptr<Player> player,
                               std::shared_ptr<RegisterPacket> packet)
{
    std::string username = packet->getUsername();
    std::string password = packet->getPassword();
    AccountDatabase &db = _rtypeServer.getAccountDatabase();

    if (player->isConnected())
        return true;
    if (username.empty() || password.empty()) {
        LOG_ERR("User " << player->getFileDescriptor() << REG_EMPTY_USERNAME_OR_PASSWORD);
        return false;
    }
    try {
        if (db.hasUsername(username)) {
            player->sendPacket(create_packet(LoginResponse, (uint8_t) 0, std::string("User already exists.")));
            return true;
        }
        std::vector<std::string> userWithPassword = db.getAllUsernamesWithPassword(password);
        if (!userWithPassword.empty()) {
            player->sendPacket(create_packet(LoginResponse, (uint8_t) 0,
                std::string(PASSWORD_USED_BY + usernameListToString(userWithPassword)) + "."));
            return true;
        }
        db.put(username, password);
        if (_rtypeServer.isConnected(username)) {
            player->sendPacket(create_packet(LoginResponse, (uint8_t) 0,
                std::string("User " + username + " already connected.")));
            return true;
        }
        player->sendPacket(create_packet(LoginResponse, 1, ""));
        player->connect(username);
        server.getPacketListener().enableAllExecutors(player);;
    } catch (const AccountDatabase::DatabaseError &e) {
        player->sendPacket(create_packet(LoginResponse, (uint8_t) 0, e.what()));
    }
    return true;
}
