/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** HealthUpdate packet
*/

#ifndef HEALTHUPDATE_PACKET_HPP
#define HEALTHUPDATE_PACKET_HPP

#include "network/packets/Packet.hpp"
#include <cstddef>
#include <iostream>
#include <memory>

class HealthUpdatePacket : public Packet
{
public:
    HealthUpdatePacket(std::size_t id = 0, float health = 0.0) :
        Packet(PacketId::HEALTH_UPDATE), id(id), health(health) {}

    enum PacketMode getMode() const {
        return PacketMode::UDP;
    }

    void serialize() {
        this->write(id);
        this->write(health);
    }
    void unserialize() {
        this->read(id);
        this->read(health);
    }
    auto getSize() const -> int { return sizeof(std::size_t) + sizeof(float); }

    const std::string getName() {
        return "HealthUpdatePacket";
    }

    void display() {
        std::cout << "Id=" << this->id << ", health=" << this->health;
    }

    std::shared_ptr<Packet> clone() const {
        return make_copy(HealthUpdatePacket);
    }
private:
    std::size_t id;
    float health;
};

#endif /* HEALTHUPDATE_PACKET_HPP */
