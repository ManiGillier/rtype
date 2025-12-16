/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** PositionUpdate packet
*/

#ifndef POSITIONUPDATE_PACKET_HPP
#define POSITIONUPDATE_PACKET_HPP

#include "network/packets/Packet.hpp"
#include <cstddef>
#include <iostream>
#include <memory>

class PositionUpdatePacket : public Packet
{
public:
    PositionUpdatePacket(std::size_t id = 0, float x = 0.0, float y = 0.0) :
        Packet(PacketId::POSITION_UPDATE), id(id), x(x), y(y) {}

    enum PacketMode getMode() const {
        return PacketMode::UDP;
    }

    void serialize() {
        this->write(id);
        this->write(x);
        this->write(y);
    }
    void unserialize() {
        this->read(id);
        this->read(x);
        this->read(y);
    }

    const std::string getName() {
        return "PositionUpdatePacket";
    }

    void display() {
        std::cout << "Id=" << this->id << ", x=" << this->x << ", y="
        << this->y;
    }
    auto getSize() const -> int { return sizeof(std::size_t)
                                         + (sizeof(float) * 2); }

    std::shared_ptr<Packet> clone() const {
        return make_copy(PositionUpdatePacket);
    }

    auto getEntityId() const -> std::size_t { return this->id; }
    auto getXPos() const -> float { return this->x; }
    auto getYPos() const -> float { return this->y; }
private:
    std::size_t id;
    float x;
    float y;
};

#endif /* POSITIONUPDATE_PACKET_HPP */
