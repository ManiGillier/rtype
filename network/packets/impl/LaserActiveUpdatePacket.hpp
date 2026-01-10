/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** LaserActiveUpdate packet
*/

#ifndef LASERACTIVEUPDATE_PACKET_HPP
#define LASERACTIVEUPDATE_PACKET_HPP

#include "network/packets/Packet.hpp"
#include <cstddef>
#include <iostream>
#include <memory>

class LaserActiveUpdatePacket : public Packet
{
public:
    LaserActiveUpdatePacket(std::size_t id = 0, bool active = false,
                            float length = 0.0) :
        Packet(PacketId::LASER_ACTIVE_UPDATE), id(id), active(active),
        length(length) {}

    enum PacketMode getMode() const override {
        return PacketMode::UDP;
    }

    void serialize() override {
        this->write(id);
        this->write(active);
        this->write(length);
    }
    void unserialize()override {
        this->read(id);
        this->read(active);
        this->read(length);
    }

    const std::string getName() override {
        return "LaserActiveUpdatePacket";
    }

    PacketDisplay display() const override {
        return {"Id", this->id, "active", this->active ? "ON" : "OFF", "length", this->length};
    }

    std::shared_ptr<Packet> clone() const override {
        return make_copy(LaserActiveUpdatePacket);
    }

    bool isEqual(const Packet &o) const override
    {
        if (o.getId() != LASER_ACTIVE_UPDATE) {
            return false;
        }
        const LaserActiveUpdatePacket &other =
            static_cast<const LaserActiveUpdatePacket &>(o);

        return (this->getLength() == other.getLength() &&
                this->isActive() == other.isActive());
    }

    auto getEntityId() const -> std::size_t { return this->id; }
    auto isActive() const -> bool { return this->active; }
    auto getLength() const -> float { return this->length; }
private:
    std::size_t id;
    bool active;
    float length;
};

#endif /* LASERACTIVEUPDATE_PACKET_HPP */
