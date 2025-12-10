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
    this->packets.push(packet);
}

void PacketSender::writePackets()
{
    std::vector<uint8_t> toSend;
    std::queue<uint8_t> packetData;

    while (!this->packets.empty()) {
        std::shared_ptr<Packet> &packet = this->packets.front();
        packet->serialize();
        toSend.push_back(packet->getId());
        packetData = packet->getData();
        while (!packetData.empty()) {
            toSend.push_back(packetData.front());
            packetData.pop();
        }
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
