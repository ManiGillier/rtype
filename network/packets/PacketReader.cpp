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

PacketReader::PacketReader(int fd)
{
    this->_fd = fd;
}

bool PacketReader::readPacket(void)
{
    if (!this->createBuffer())
        return false;
    while (true) {
        if (readData.empty())
            return true;
        if (currentPacket == nullptr) {
            currentPacket = PacketManager::getInstance().createPacketById(readData.front());
            readData.pop();
        }
        if (currentPacket == nullptr) {
            LOG_ERR("Received wrong packet, disconnecting " << this->_fd << std::endl);
            return false;
        }
        std::size_t packetSize = (std::size_t) currentPacket->getSize();
        if (packetSize > readData.size())
            return true;
        std::queue<uint8_t> _arr;
        for (std::size_t i = 0; i < packetSize; i++) {
            _arr.push(readData.front());
            readData.pop();
        }
        currentPacket->setData(_arr);
        currentPacket->unserialize();
        receivedPackets.push(currentPacket);
        PacketLogger::logPacket(currentPacket,
                 PacketLogger::PacketMethod::RECEIVED, this->_fd);
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
        this->readData.push(_readBuff[i]);
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
