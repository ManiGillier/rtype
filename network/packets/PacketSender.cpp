/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** PacketSender
*/

#include <iostream>
#include <unistd.h>
#include "network/packets/Packet.hpp"
#include "PacketLogger.hpp"
#include "PacketSender.hpp"

PacketSender::PacketSender(int fd)
{
    this->_fd = fd;
}

void PacketSender::sendPacket(std::shared_ptr<Packet> packet)
{
    packet->clearData();
    try {
        packet->serialize();
    } catch (const Packet::PacketException &e) {
        LOG_ERR(e.what());
        return;
    }
    this->dataQueue.push_back(packet->getId());
    this->dataQueue.insert(this->dataQueue.end(),
        packet->getData().begin(), packet->getData().end());
    this->pendingPacket.emplace(packet, 1 + packet->getData().size());
}

void PacketSender::writePackets()
{
    ssize_t bytesWritten = write(this->_fd, this->dataQueue.data(),
        this->dataQueue.size());

    if (bytesWritten < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
            return;
        this->dataQueue.clear();
        return;
    }
    this->dataQueue.erase(this->dataQueue.begin(),
        this->dataQueue.begin() + bytesWritten);
    while (!this->pendingPacket.empty() && lastWritten + bytesWritten >= std::get<1>(this->pendingPacket.front())) {
        PacketLogger::logPacket(std::get<0>(this->pendingPacket.front()),
                PacketLogger::PacketMethod::SENT, this->_fd);
        this->lastWritten -= std::get<1>(this->pendingPacket.front());
        this->pendingPacket.pop();
    }
}

void PacketSender::setFd(int fd)
{
    this->_fd = fd;
}

bool PacketSender::shouldSend() const
{
    return !this->dataQueue.empty();
}
