/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** HitboxSizeUpdate packet
*/

#ifndef HITBOXSIZEUPDATE_PACKET_HPP
#define HITBOXSIZEUPDATE_PACKET_HPP

#include "network/packets/Packet.hpp"
#include <cstddef>
#include <iostream>
#include <memory>

class HitboxSizeUpdatePacket : public Packet
{
public:
    HitboxSizeUpdatePacket(std::size_t id = 0, float width = 0.0,
                           float height = 0.0) :
        Packet(PacketId::HITBOX_SIZE_UPDATE), id(id), width(width),
        height(height) {}

    enum PacketMode getMode() const {
        return PacketMode::TCP;
    }

    void serialize() {
        this->write(id);
        this->write(width);
        this->write(height);
    }
    void unserialize() {
        this->read(id);
        this->read(width);
        this->read(height);
    }
    const std::string getName() {
        return "HitboxSizeUpdatePacket";
    }

    PacketDisplay display() const {
        return {"Id", this->id, "width", this->width, "height", this->height};
    }

    std::shared_ptr<Packet> clone() const {
        return make_copy(HitboxSizeUpdatePacket);
    }

    auto getEntityId() const -> std::size_t { return this->id; }
    auto getWidth() const -> float { return this->width; }
    auto getHeight() const -> float { return this->height; }
private:
    std::size_t id;
    float width;
    float height;
};

#endif /* HITBOXSIZEUPDATE_PACKET_HPP */
