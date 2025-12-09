/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** PacketManager
*/

#include "PacketManager.hpp"
#include "network/packets/impl/PlayerPositionPacket.hpp"
#include "impl/StartRequestPacket.hpp"
#include "impl/ScoreUpdatePacket.hpp"
#include "impl/GameStartPacket.hpp"
#include "impl/PlayerDeadPacket.hpp"
#include "impl/PlayerJoinPacket.hpp"
#include "impl/PlayerWonPacket.hpp"
#include "impl/PlayerLostPacket.hpp"
#include "impl/GhostPlayerPositionPacket.hpp"
#include "impl/GhostScoreUpdatePacket.hpp"

void PacketManager::registerPackets()
{
    this->packets.push_back(std::make_shared<PlayerPositionPacket>());
    this->packets.push_back(std::make_shared<StartRequestPacket>());
    this->packets.push_back(std::make_shared<ScoreUpdatePacket>());
    this->packets.push_back(std::make_shared<GameStartPacket>());
    this->packets.push_back(std::make_shared<PlayerDeadPacket>());
    this->packets.push_back(std::make_shared<PlayerJoinPacket>());
    this->packets.push_back(std::make_shared<PlayerWonPacket>());
    this->packets.push_back(std::make_shared<PlayerLostPacket>());
    this->packets.push_back(std::make_shared<GhostPlayerPositionPacket>());
    this->packets.push_back(std::make_shared<GhostScoreUpdatePacket>());
}

std::optional<std::shared_ptr<Packet>> PacketManager::createPacketById(uint8_t id) const
{
    for (const std::shared_ptr<Packet> &packet : this->packets) {
        if (packet->getId() == id)
            return packet->clone();
    }
    return std::nullopt;
}

bool PacketManager::hasPacketById(uint8_t id) const
{
    for (const std::shared_ptr<Packet> &packet : this->packets) {
        if (packet->getId() == id)
            return true;
    }
    return false;
}
