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
#include "impl/AuthentifiedPacket.hpp"
#include "impl/SAuthentificationPacket.hpp"
#include "impl/CAuthentificationPacket.hpp"


void PacketManager::registerPackets()
{
    this->packets.push_back(std::make_shared<ScoreUpdatePacket>());
    this->packets.push_back(std::make_shared<SAuthentificationPacket>());
    this->packets.push_back(std::make_shared<CAuthentificationPacket>());
    this->packets.push_back(std::make_shared<AuthentifiedPacket>());
}

std::shared_ptr<Packet> PacketManager::createPacketById(uint8_t id, Packet::PacketMode mode) const
{
    for (const std::shared_ptr<Packet> &packet : this->packets) {
        if (packet->getId() == id && packet->getMode() == mode)
            return packet->clone();
    }
    return nullptr;
}

bool PacketManager::hasPacketById(uint8_t id) const
{
    for (const std::shared_ptr<Packet> &packet : this->packets) {
        if (packet->getId() == id)
            return true;
    }
    return false;
}
