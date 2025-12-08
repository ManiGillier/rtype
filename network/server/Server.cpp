/*
** EPITECH PROJECT, 2025
** rtype [WSL: Ubuntu-24.04]
** File description:
** Server
*/

#include "Logger.hpp"
#include "Server.hpp"
#include "client/Client.hpp"

Server::Server(int port)
{
    this->port = port;
}

bool Server::up()
{
    LOG("Starting server at " << this->port << "..");

    return this->upStatus;
}

bool Server::down()
{
    LOG("Stopping server at " << this->port << "..");
    return this->upStatus;
}

bool Server::isUp() const
{
    return this->upStatus;
}

void Server::loop()
{
    if (!this->upStatus)
        return;
}

PacketListener &Server::getPacketListener()
{
    return this->pl;
}

std::vector<Client> &Server::getClients()
{
    return this->clients;
}
