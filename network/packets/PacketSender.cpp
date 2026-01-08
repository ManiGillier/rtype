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
    this->packets.push(packet);
}

void PacketSender::writePackets()
{
    std::vector<uint8_t> toSend;

    while (!this->packets.empty()) {
        std::shared_ptr<Packet> &packet = this->packets.front();
        packet->clearData();
        packet->serialize();
        toSend.push_back(packet->getId());
        std::vector<uint8_t> &packetData = packet->getData();
        toSend.insert(toSend.end(), packetData.begin(), packetData.end());
        PacketLogger::logPacket(packet,
                PacketLogger::PacketMethod::SENT, this->_fd);
        this->packets.pop();
    }
    write(this->_fd, toSend.data(), toSend.size());
}
std::queue<std::shared_ptr<Packet>> PacketSender::getPackets() const
{
    return this->packets;
}

void PacketSender::setFd(int fd)
{
    this->_fd = fd;
}
