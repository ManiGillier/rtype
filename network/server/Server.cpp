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

bool Server::up() const
{
    LOG("Starting server at " << this->port << "..");

    return false;
}

bool Server::down() const
{
    LOG("Stopping server at " << this->port << "..");
    return false;
}

void Server::loop()
{
    
}

std::vector<Client> &Server::getClients()
{
    return this->clients;
}
