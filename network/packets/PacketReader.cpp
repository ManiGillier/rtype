/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** PacketReader
*/

#include <array>
#include <cstdint>
#include <unistd.h>
#include <vector>
#include <iostream>
#include "PacketReader.hpp"
#include "Packet.hpp"
#include "PacketLogger.hpp"
#include <network/packets/PacketManager.hpp>

PacketReader::PacketReader(int fd, Packet::PacketMode mode)
{
    this->_fd = fd;
    this->mode = mode;
}

bool PacketReader::readPacket(void)
{
    if (!this->createBuffer())
        return false;
    while (true) {
        if (readData.empty())
            return true;
        uint8_t packetId = 0;
        if (currentPacket == nullptr) {
            packetId = readData[0];
            currentPacket = PacketManager::getInstance().createPacketById(packetId, this->mode);
            readData.erase(readData.begin());
        }
        if (currentPacket == nullptr) {
            LOG_ERR("Received wrong packet, disconnecting " << this->_fd << "(ID=" << (int) packetId  << ")");
            return false;
        }
        currentPacket->setData(readData);
        try {
            currentPacket->unserialize();
        } catch (const std::exception &) {
            return true;
        }
        receivedPackets.push(currentPacket);
        PacketLogger::logPacket(currentPacket,
            PacketLogger::PacketMethod::RECEIVED, this->_fd);
        readData.erase(readData.begin(), std::next(readData.begin(),
            static_cast<std::ptrdiff_t>(currentPacket->getReadCursor())));
        currentPacket = nullptr;
    }
    return true;
}

bool PacketReader::createBuffer(void)
{
    ssize_t newlyReadBytes = 0;
    uint8_t _readBuff[BUFFER_SIZE] = {0};

    newlyReadBytes = read(this->_fd, _readBuff, BUFFER_SIZE);
    if (newlyReadBytes == 0)
        return false;
    for (ssize_t i = 0; i < newlyReadBytes; i++)
        this->readData.push_back(_readBuff[i]);
    return true;
}

 std::queue<std::shared_ptr<Packet>> &PacketReader::getReceivedPackets()
{
    return this->receivedPackets;
}

void PacketReader::setFd(int fd)
{
    this->_fd = fd;
}
