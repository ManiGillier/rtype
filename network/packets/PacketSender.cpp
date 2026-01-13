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
#include "PacketCompressor.hpp"
#include "PacketSender.hpp"

PacketSender::PacketSender(int fd)
{
    this->_fd = fd;
}

void PacketSender::sendPacket(std::shared_ptr<Packet> packet)
{
    std::vector<uint8_t> compressed;

    packet->clearData();
    try {
        packet->serialize();
        compressed = PacketCompressor::compress(packet->getData());
    } catch (const Packet::PacketException &e) {
        LOG_ERR(e.what());
        return;
    }
    this->dataQueue.push_back(packet->getId());
    uint32_t oldPacketSize = (uint32_t) packet->getData().size();
    uint32_t newPacketSize =  (uint32_t) compressed.size();
    for (uint8_t bin : Packet::toBinary(oldPacketSize))
        this->dataQueue.push_back(bin);
    for (uint8_t bin : Packet::toBinary(newPacketSize))
        this->dataQueue.push_back(bin);
    this->dataQueue.insert(this->dataQueue.end(),
        compressed.begin(), compressed.end());
    this->pendingPacket.emplace(packet, 1 + 4 + 4 + compressed.size());
}

void PacketSender::writePackets()
{
    ssize_t bytesWritten = write(this->_fd, this->dataQueue.data(),
        this->dataQueue.size());

    if (bytesWritten < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
            return;
        this->dataQueue.clear();
        this->pendingPacket = {};
        this->lastWritten = 0;
        return;
    }
    
    this->dataQueue.erase(this->dataQueue.begin(),
        this->dataQueue.begin() + bytesWritten);
    this->lastWritten += bytesWritten;
    while (!this->pendingPacket.empty() && 
           this->lastWritten >= std::get<1>(this->pendingPacket.front())) {
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
