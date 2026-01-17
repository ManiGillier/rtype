/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** LoginExecutor
*/

#include <network/logger/Logger.hpp>
#include <network/packets/impl/LoginPacket.hpp>
#include <network/packets/impl/LoginResponse.hpp>
#include "../../database/AccountDatabase.hpp"
#include "../server/RTypeServer.hpp"
#include "LoginExecutor.hpp"

LoginExecutor::LoginExecutor(RTypeServer &server) : _rtypeServer(server) {}

bool LoginExecutor::execute(Server &server, std::shared_ptr<Player> player,
                            std::shared_ptr<LoginPacket> packet)
{
    std::string username = packet->getUsername();
    std::string password = packet->getPassword();
    AccountDatabase &db = _rtypeServer.getAccountDatabase();

    if (player->isConnected())
        return true;
    if (username.empty() || password.empty()) {
        LOG_ERR("User " << player->getFileDescriptor() << LOG_EMPTY_USERNAME_OR_PASSWORD);
        return false;
    }
    try {
        if (!db.hasUsername(username)) {
            player->sendPacket(create_packet(LoginResponse, (uint8_t) 0, std::string("No user " + username + " already exists.")));
            return true;
        }
        if (_rtypeServer.isConnected(username)) {
            player->sendPacket(create_packet(LoginResponse, (uint8_t) 0,
                std::string("User " + username + " already connected.")));
            return true;
        }
        std::string realPassword = db.getPasswordByUsername(username);
        if (realPassword == password) {
            if (db.isBanned(username)) {
                player->sendPacket(create_packet(LoginResponse, 0, "You were banned from the server."));
                return true;
            }
            player->sendPacket(create_packet(LoginResponse, 1, ""));
            player->connect(username);
            server.getPacketListener().enableAllExecutors(player);
            try {
                player->setScore(db.getScore(username));
            } catch (AccountDatabase::DatabaseError &e) {
                LOG_ERR(e.what());
            }
        } else {
            player->sendPacket(create_packet(LoginResponse, 0, "Sorry, the password isn't right, you probably meant to type: " + realPassword));
        }
    } catch (const AccountDatabase::DatabaseError &e) {
        player->sendPacket(create_packet(LoginResponse, (uint8_t) 0, e.what()));
    }
    (void) server;
    return true;
}
