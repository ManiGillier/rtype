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
    LaserActiveUpdatePacket(std::size_t id = 0, bool active = false) :
        Packet(PacketId::LASER_ACTIVE_UPDATE), id(id), active(active) {}

    enum PacketMode getMode() const {
        return PacketMode::UDP;
    }

    void serialize() {
        this->write(id);
        this->write(active);
    }
    void unserialize() {
        this->read(id);
        this->read(active);
    }

    const std::string getName() {
        return "LaserActiveUpdatePacket";
    }

    void display() {
        std::cout << "Id=" << this->id << ", "
        << (this->active ? "ON" : "OFF");
    }
    auto getSize() const -> int { return sizeof(std::size_t) + sizeof(bool); }

    std::shared_ptr<Packet> clone() const {
        return make_copy(LaserActiveUpdatePacket);
    }

    auto getEntityId() const -> std::size_t { return this->id; }
    auto isActive() const -> bool { return this->active; }
private:
    std::size_t id;
    bool active;
};

#endif /* LASERACTIVEUPDATE_PACKET_HPP */
