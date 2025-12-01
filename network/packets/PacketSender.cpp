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

void PacketSender::sendPacket(Packet *packet)
{
    packet->clearData();
    this->packets.push(packet);
}

void PacketSender::sendPackets(std::queue<Packet *> packets)
{
    while (!packets.empty()) {
        this->sendPacket(packets.front());
        packets.pop();
    }
}

void PacketSender::writePackets()
{
    std::vector<uint8_t> toSend;
    std::queue<uint8_t> packetData;
    Packet *packet = nullptr;

    while (!this->packets.empty()) {
        packet = this->packets.front();
        packet->serialize();
        toSend.push_back(packet->getId());
        packetData = packet->getData();
        while (!packetData.empty()) {
            toSend.push_back(packetData.front());
            packetData.pop();
        }
        if (shouldLog)
            PacketLogger::logPacket(packet,
                PacketLogger::PacketMethod::SENT, this->_fd);
        this->packets.pop();
    }
    write(this->_fd, toSend.data(), toSend.size());
}

std::queue<Packet *> PacketSender::getPackets() const
{
    return this->packets;
}
