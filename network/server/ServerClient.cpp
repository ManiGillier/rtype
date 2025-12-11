/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** Client
*/

#include <network/logger/Logger.hpp>
#include <network/server/ServerClient.hpp>
#include <unistd.h>
#include <poll.h>

ServerClient::ServerClient(int fd, PollManager &pm) : Pollable(fd, pm), pm(pm)
{
    return;
}

short ServerClient::getFlags() const
{
    short flags = POLLIN;

    if (this->shouldWrite())
        flags |= POLLOUT;
    return flags;
}

bool ServerClient::receiveEvent(short event)
{
    if ((event & POLLIN) != 0) {
        if (!this->getPacketReader().readPacket())
            return false;
        std::queue<std::shared_ptr<Packet>> &upcomingPackets =
            this->getPacketReader().getReceivedPackets();
        while (!upcomingPackets.empty()) {
            toProcess.push(upcomingPackets.front());
            upcomingPackets.pop();
        }
    }
    if (shouldWrite() && (event & POLLOUT) != 0) {
        this->getPacketSender().writePackets();
        return true;
    }
    return true;
}

bool ServerClient::shouldWrite() const
{
    return !this->getPacketSender().getPackets().empty();
}
