/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** DespawnBullet packet
*/

#ifndef DESPAWNBULLET_PACKET_HPP
#define DESPAWNBULLET_PACKET_HPP

#include "network/packets/Packet.hpp"
#include <cstddef>
#include <iostream>
#include <memory>

class DespawnBulletPacket : public Packet
{
public:
    DespawnBulletPacket(std::size_t id = 0) :
        Packet(PacketId::DESPAWN_BULLET), id(id) {}

    enum PacketMode getMode() const {
        return PacketMode::TCP;
    }

    void serialize() {
        this->write(id);
    }
    void unserialize() {
        this->read(id);
    }

    auto getSize() const -> int { return sizeof(std::size_t); }

    const std::string getName() {
        return "DespawnBulletPacket";
    }

    void display() {
        std::cout << "Id=" << this->id;
    }

    std::shared_ptr<Packet> clone() const {
        return make_copy(DespawnBulletPacket);
    }
private:
    std::size_t id;
};

#endif /* DESPAWNBULLET_PACKET_HPP */
