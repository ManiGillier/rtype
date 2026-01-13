/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** RegisterExecutor
*/

#include "RegisterExecutor.hpp"

RegisterExecutor::RegisterExecutor(RTypeServer &server) : _rtypeServer(server) {}

bool RegisterExecutor::execute(Server &server, std::shared_ptr<Player> player,
                               std::shared_ptr<RegisterPacket> packet)
{
    (void) server;
    (void) player;
    (void) packet;
    LOG("OH LE REGISTER POGGERRSSSSS");
    return true;
}
