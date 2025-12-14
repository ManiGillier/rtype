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
    HealthUpdatePacket(std::size_t id = 0, float health = 0.0,
                       float max_health = 0.0) :
        Packet(PacketId::HEALTH_UPDATE), id(id), health(health),
        max_health(max_health) {}

    enum PacketMode getMode() const {
        return PacketMode::UDP;
    }

    void serialize() {
        this->write(id);
        this->write(health);
        this->write(max_health);
    }
    void unserialize() {
        this->read(id);
        this->read(health);
        this->read(max_health);
    }
    auto getSize() const -> int { return sizeof(std::size_t)
                                         + (sizeof(float) * 2); }

    const std::string getName() {
        return "HealthUpdatePacket";
    }

    void display() {
        std::cout << "Id=" << this->id << ", health=" << this->health
        << ", max_health=" << this->max_health;
    }

    std::shared_ptr<Packet> clone() const {
        return make_copy(HealthUpdatePacket);
    }

    auto getEntityId() const -> std::size_t { return this->id; }
    auto getHealth() const -> float { return this->health; }
    auto getMaxHealth() const -> float { return this->max_health; }
private:
    std::size_t id;
    float health;
    float max_health;
};

#endif /* HEALTHUPDATE_PACKET_HPP */
