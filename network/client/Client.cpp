/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** Client
*/

#include <network/client/Client.hpp>
#include <network/logger/Logger.hpp>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include "Client.hpp"

Client::Client(std::string ip, int port)
{
    this->ip = ip;
    this->port = port;
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    int optVal = 1;

    this->fd = serverSocket;
    if (serverSocket != -1)
        setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR,
               &optVal, sizeof(optVal));
}

bool Client::connect()
{
    int af = -1;
    struct sockaddr_in params;

    if (this->connected)
        return false;
    LOG("Trying to connect to " << ip << ":" << port << "..");
    if (this->fd == -1)
        return false;
    if (inet_pton(AF_INET, this->ip.c_str(), &af) != 1)
        return this->connected;

    memset(&params, 0, sizeof(sockaddr));
    params.sin_family = AF_INET;
    params.sin_addr.s_addr = (in_addr_t) af;
    params.sin_port = htons(this->port);
    int connectValue = ::connect(this->fd, (struct sockaddr *) &params,
                               sizeof(struct sockaddr_in));
    if (connectValue == -1) {
        return false;
    }
    this->connected = true;
    return this->connected;
}

bool Client::disconnect()
{
    LOG("Trying to disconnect from " << this->ip << ":" << this->port << "..")

    if (!this->connected)
        return false;
    if (this->fd == -1)
        return false;

    close(this->fd);
    this->fd = -1;
    this->connected = false;
    return true;
}
bool Client::isConnected() const
{
    return this->connected;
}

const std::string &Client::getIp() const
{
    return this->ip;
}

const int Client::getPort() const
{
    return this->port;
}
