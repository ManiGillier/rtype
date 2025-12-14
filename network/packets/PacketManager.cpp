/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** PacketManager
*/

#include "PacketManager.hpp"

#include "impl/ClientInputsPacket.hpp"
#include "impl/DespawnBulletPacket.hpp"
#include "impl/DespawnPlayerPacket.hpp"
#include "impl/EnemyDiedPacket.hpp"
#include "impl/GameOverPacket.hpp"
#include "impl/HealthUpdatePacket.hpp"
#include "impl/HitboxSizeUpdatePacket.hpp"
#include "impl/LaserActiveUpdatePacket.hpp"
#include "impl/NewBulletPacket.hpp"
#include "impl/NewEnemyPacket.hpp"
#include "impl/NewPlayerPacket.hpp"
#include "impl/PlayerDiedPacket.hpp"
#include "impl/PlayerHitPacket.hpp"
#include "impl/PlayerIdPacket.hpp"
#include "impl/PositionUpdatePacket.hpp"

void PacketManager::registerPackets()
{
    this->packets.push_back(std::make_shared<ClientInputsPacket>());
    this->packets.push_back(std::make_shared<DespawnBulletPacket>());
    this->packets.push_back(std::make_shared<DespawnPlayerPacket>());
    this->packets.push_back(std::make_shared<EnemyDiedPacket>());
    this->packets.push_back(std::make_shared<GameOverPacket>());
    this->packets.push_back(std::make_shared<HealthUpdatePacket>());
    this->packets.push_back(std::make_shared<HitboxSizeUpdatePacket>());
    this->packets.push_back(std::make_shared<LaserActiveUpdatePacket>());
    this->packets.push_back(std::make_shared<NewBulletPacket>());
    this->packets.push_back(std::make_shared<NewEnemyPacket>());
    this->packets.push_back(std::make_shared<NewPlayerPacket>());
    this->packets.push_back(std::make_shared<PlayerDiedPacket>());
    this->packets.push_back(std::make_shared<PlayerHitPacket>());
    this->packets.push_back(std::make_shared<PlayerIdPacket>());
    this->packets.push_back(std::make_shared<PositionUpdatePacket>());
}

std::shared_ptr<Packet> PacketManager::createPacketById(uint8_t id) const
{
    for (const std::shared_ptr<Packet> &packet : this->packets) {
        if (packet->getId() == id)
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
