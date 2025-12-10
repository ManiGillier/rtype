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

Client::Client(const std::string &ip, int port)
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
    params.sin_port = (in_port_t) htons((uint16_t) this->port);
    int connectValue = ::connect(this->fd, (struct sockaddr *) &params,
                               sizeof(struct sockaddr_in));
    if (connectValue == -1) {
        return false;
    }
    this->connected = true;
    this->pm.addPollable(std::make_shared<ClientPollable>(*this, this->fd));
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

void Client::loop()
{
    if (!this->connected)
        return;
    this->getPollManager().pollSockets();
}

const std::string &Client::getIp() const
{
    return this->ip;
}

int Client::getPort() const
{
    return this->port;
}

PollManager &Client::getPollManager()
{
    return this->pm;
}

ClientPollable::ClientPollable(Client &cl, int fd) : Pollable(fd), cl(cl)
{
    return;
}

short ClientPollable::getFlags() const
{
    short flags = POLLIN;

    if (this->shouldWrite())
        flags |= POLLOUT;
    return flags;
}

bool ClientPollable::receiveEvent(short revent)
{
    if ((revent & POLLIN) != 0) {
        if (!this->getPacketReader().readPacket())
            return false;
        std::queue<std::shared_ptr<Packet>> &upcomingPackets =
            this->getPacketReader().getReceivedPackets();
        while (!upcomingPackets.empty()) {
            toProcess.push(upcomingPackets.front());
            upcomingPackets.pop();
        }
    }
    if (shouldWrite() && (revent & POLLOUT) != 0) {
        this->getPacketSender().writePackets();
        return true;
    }
    return true;
}

void ClientPollable::sendPacket(std::shared_ptr<Packet> &p)
{
    this->getPacketSender().sendPacket(p);
    this->cl.getPollManager().updateFlags(this->getFileDescriptor(), this->getFlags());
}

std::queue<std::shared_ptr<Packet>> &ClientPollable::getReceivedPackets()
{
    return this->toProcess;
}

bool ClientPollable::shouldWrite() const
{
    return !this->getPacketSender().getPackets().empty();
}
