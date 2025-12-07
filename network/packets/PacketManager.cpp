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
    this->packets.push_back(std::make_unique<PlayerPositionPacket>());
    this->packets.push_back(std::make_unique<StartRequestPacket>());
    this->packets.push_back(std::make_unique<ScoreUpdatePacket>());
    this->packets.push_back(std::make_unique<GameStartPacket>());
    this->packets.push_back(std::make_unique<PlayerDeadPacket>());
    this->packets.push_back(std::make_unique<PlayerJoinPacket>());
    this->packets.push_back(std::make_unique<PlayerWonPacket>());
    this->packets.push_back(std::make_unique<PlayerLostPacket>());
    this->packets.push_back(std::make_unique<GhostPlayerPositionPacket>());
    this->packets.push_back(std::make_unique<GhostScoreUpdatePacket>());
}

std::optional<std::unique_ptr<Packet>> PacketManager::getPacketById(uint8_t id) const
{
    for (const std::unique_ptr<Packet> &packet : this->packets) {
        if (packet->getId() == id)
            return packet->clone();
    }
    return std::nullopt;
}

bool PacketManager::hasPacketById(uint8_t id) const
{
    for (const std::unique_ptr<Packet> &packet : this->packets) {
        if (packet->getId() == id)
            return true;
    }
    return false;
}
