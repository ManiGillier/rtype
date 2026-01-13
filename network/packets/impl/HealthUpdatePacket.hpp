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

    enum PacketMode getMode() const override {
        return PacketMode::UDP;
    }

    void serialize() override {
        this->write(id);
        this->write(health);
        this->write(max_health);
    }
    void unserialize() override {
        this->read(id);
        this->read(health);
        this->read(max_health);
    }
    const std::string getName() override {
        return "HealthUpdatePacket";
    }

    PacketDisplay display() const override {
        return {"Id", this->id, "health", this->health, "max_health", this->max_health};
    }

    std::shared_ptr<Packet> clone() const override {
        return make_copy(HealthUpdatePacket);
    }

    bool isEqual(const Packet &o) const override
    {
        if (o.getId() != HEALTH_UPDATE) {
            return false;
        }
        const HealthUpdatePacket &other =
            static_cast<const HealthUpdatePacket &>(o);

        return (this->getHealth() == other.getHealth() &&
                this->getMaxHealth() == other.getMaxHealth());
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
