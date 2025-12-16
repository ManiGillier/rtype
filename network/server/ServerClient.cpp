/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** Client
*/

#include <network/logger/Logger.hpp>
#include <network/server/ServerClient.hpp>
#include <network/server/Server.hpp>
#include <unistd.h>
#include <poll.h>
#include "ServerClient.hpp"

ServerClient::ServerClient(int fd, Server &s) : Pollable(fd, s.getPollManager()), serv(s)
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

void ServerClient::sendPacket(std::shared_ptr<Packet> p, bool wakeUpPoll)
{
    if (p->getMode() == Packet::PacketMode::TCP) {
        this->getPacketSender().sendPacket(p);
        this->serv.getPollManager().updateFlags(this->getFileDescriptor(),
        this->getFlags());
    } else {
        std::lock_guard<std::mutex> lck(this->serv.udpLock);
        toProcessUDP.emplace_back(p, this->getClientAddress());
    }
    if (wakeUpPoll)
        this->serv.getPollManager().wakeUp();
}

bool ServerClient::shouldWrite() const
{
    return !this->getPacketSender().getPackets().empty();
}
