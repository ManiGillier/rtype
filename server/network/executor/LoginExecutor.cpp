/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** LoginExecutor
*/

#include "LoginExecutor.hpp"

LoginExecutor::LoginExecutor(RTypeServer &server) : _rtypeServer(server) {}

bool LoginExecutor::execute(Server &server, std::shared_ptr<Player> player,
                            std::shared_ptr<LoginPacket> packet)
{
    (void) server;
    (void) player;
    (void) packet;
    return true;
}
