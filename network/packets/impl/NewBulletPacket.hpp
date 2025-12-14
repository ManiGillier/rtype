/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** NewBullet packet
*/

#ifndef NEWBULLET_PACKET_HPP
#define NEWBULLET_PACKET_HPP

#include "network/packets/Packet.hpp"
#include <cstddef>
#include <iostream>
#include <memory>

class NewBulletPacket : public Packet
{
public:
    NewBulletPacket(std::size_t id = 0) :
        Packet(PacketId::NEW_BULLET), id(id) {}

    enum PacketMode getMode() const {
        return PacketMode::TCP;
    }

    void serialize() {
        this->write(id);
    }
    void unserialize() {
        this->read(id);
    }

    const std::string getName() {
        return "NewBulletPacket";
    }

    void display() {
        std::cout << "Id=" << this->id;
    }
    auto getSize() const -> int { return sizeof(std::size_t); }

    std::shared_ptr<Packet> clone() const {
        return make_copy(NewBulletPacket);
    }
private:
    std::size_t id;
};

#endif /* NEWBULLET_PACKET_HPP */
