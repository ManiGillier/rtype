/*
** EPITECH PROJECT, 2025
** rtype [WSL: Ubuntu-24.04]
** File description:
** Server
*/

#include <network/logger/Logger.hpp>
#include <network/server/Server.hpp>
#include <network/server/ServerClient.hpp>
#include <network/server/Server.hpp>
#include <string>

/* TODO: FIND CPP INCLUDES AS WELL */
#include <poll.h>
#include <unistd.h>
#include <poll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <bits/stdc++.h>

Server::Server(int port)
{
    this->port = port;
}

bool Server::up()
{
    LOG("Starting server at " << this->port << "..");

    if (this->upStatus)
        return false;
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    int optVal = 1;
    struct sockaddr_in params;

    memset(&params, 0, sizeof(sockaddr));
    params.sin_family = AF_INET;
    params.sin_addr.s_addr = INADDR_ANY;
    params.sin_port = htons((uint16_t) port);
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &optVal, sizeof(optVal));
    if (bind(serverSocket, (struct sockaddr *) &params, sizeof(struct sockaddr_in)) == -1)
        return this->upStatus;
    if (listen(serverSocket, SOMAXCONN) == -1)
        return this->upStatus;
    this->upStatus = true;
    this->fd = serverSocket;
    this->getPollManager().addPollable(
        std::make_shared<ServerPollable>(*this, fd));
    LOG("Could start server at " << this->port << " !");
    return this->upStatus;
}

/*
    TODO: Erase all datas
*/
bool Server::down()
{
    LOG("Stopping server at " << this->port << "..");
    if (this->upStatus)
        shutdown(this->fd, SHUT_RDWR);
    LOG("Could stop server at " << this->port << " !");
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
    this->getPollManager().pollSockets();
    /* TODO : Execute packets */
}

PacketListener &Server::getPacketListener()
{
    return this->pl;
}

PollManager &Server::getPollManager()
{
    return this->pm;
}

ServerPollable::ServerPollable(Server &server, int fd) : Pollable(fd), server(server)
{
    return;
}

short ServerPollable::getFlags() const
{
    return POLLIN;
}

bool ServerPollable::receiveEvent(short revent)
{
    int other_socket = accept(this->getFileDescriptor(), 0, 0);
    std::shared_ptr<IPollable> createdClient = nullptr;

    (void) revent;
    if (other_socket < 0)
        return true;
    createdClient = server.createClient(other_socket);
    this->server.getPollManager().addPollable(createdClient);
    this->server.onClientConnect(createdClient);
    return true;
}
