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
#include "PacketCompressor.hpp"
#include <network/packets/PacketManager.hpp>

PacketReader::PacketReader(int fd, Packet::PacketMode mode)
{
    this->_fd = fd;
    this->mode = mode;
}

bool PacketReader::readPacket(void)
{
    if (!this->createBuffer()) {
        currentPacket = nullptr;
        originalSize = -1;
        compressedSize = -1;
        return false;
    }
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
        if (readData.size() < sizeof(uint32_t) * 2 && originalSize == -1)
            return true;
        if (originalSize == -1) {
            uint32_t origSize = 0;
            uint32_t compSize = 0;
            Packet::fromBinary(readData, origSize);
            Packet::fromBinary(readData, compSize);
            if (origSize > MAX_PACKET_SIZE || compSize > MAX_PACKET_SIZE) {
                LOG_ERR("Packet size too large, disconnecting " << this->_fd);
                currentPacket = nullptr;
                originalSize = -1;
                compressedSize = -1;
                return false;
            }
            this->originalSize = (int32_t) origSize;
            this->compressedSize = (int32_t) compSize;
        }
        if (readData.size() < (std::size_t) this->compressedSize)
            return true;
        try {
            std::vector<uint8_t> dataPacket = PacketCompressor::decompress(readData, (std::size_t) originalSize,
                (std::size_t) compressedSize);
            currentPacket->setData(dataPacket);
            currentPacket->unserialize();
            receivedPackets.push(currentPacket);
            PacketLogger::logPacket(currentPacket,
            PacketLogger::PacketMethod::RECEIVED, this->_fd);
        } catch (const Packet::PacketException &e) {
            LOG_ERR(e.what());
            return true;
        }
        readData.erase(readData.begin(), std::next(readData.begin(),
            static_cast<std::ptrdiff_t>(compressedSize)));
        currentPacket = nullptr;
        originalSize = -1;
        compressedSize = -1;
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
