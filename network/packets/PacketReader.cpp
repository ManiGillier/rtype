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

#include "impl/GhostScoreUpdatePacket.hpp"
#include "impl/GameStartPacket.hpp"
#include "impl/PlayerDeadPacket.hpp"
#include "impl/PlayerJoinPacket.hpp"
#include "impl/PlayerPositionPacket.hpp"
#include "impl/ScoreUpdatePacket.hpp"
#include "impl/StartRequestPacket.hpp"
#include "impl/GhostPlayerPositionPacket.hpp"
#include "impl/PlayerLostPacket.hpp"
#include "impl/PlayerWonPacket.hpp"

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
            currentPacket = this->buildPacket(readData.front());
            readData.pop();
        }
        if (!currentPacket) {
            LOG_ERR("Received wrong packet, disconnecting " << this->_fd << std::endl);
            return false;
        }
        std::size_t packetSize = currentPacket->getSize();
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
    std::size_t newlyReadBytes = 0;
    char _readBuff[BUFFER_SIZE] = {0};

    newlyReadBytes = read(this->_fd, _readBuff, BUFFER_SIZE);
    if (newlyReadBytes == 0)
        return false;
    for (std::size_t i = 0; i < newlyReadBytes; i++)
        this->readData.push(_readBuff[i]);
    return true;
}

Packet *PacketReader::buildPacket(char packetId)
{
    switch (packetId) {
        case 1:
            return new PlayerPositionPacket();
        case 2:
            return new StartRequestPacket();
        case 3:
            return new ScoreUpdatePacket();
        case 4:
            return new GameStartPacket();
        case 5:
            return new PlayerDeadPacket();
        case 6:
            return new PlayerJoinPacket();
        case 8:
            return new PlayerWonPacket();
        case 9:
            return new PlayerLostPacket();
        case 10:
            return new GhostPlayerPositionPacket();
        case 11:
            return new GhostScoreUpdatePacket();
    }
    return nullptr;
}

std::queue<Packet *> &PacketReader::getReceivedPackets()
{
    return this->receivedPackets;
}

void PacketReader::setFd(int fd)
{
    this->_fd = fd;
}
