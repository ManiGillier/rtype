/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** NewEnemy packet
*/

#ifndef NEWENEMY_PACKET_HPP
#define NEWENEMY_PACKET_HPP

#include "network/packets/Packet.hpp"
#include <cstddef>
#include <iostream>
#include <memory>

class NewEnemyPacket : public Packet
{
public:
    NewEnemyPacket(std::size_t id = 0) :
        Packet(PacketId::NEW_ENEMY), id(id) {}

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
        return "NewEnemyPacket";
    }

    void display() {
        std::cout << "Id=" << this->id;
    }
    auto getSize() const -> int { return sizeof(std::size_t); }

    std::shared_ptr<Packet> clone() const {
        return make_copy(NewEnemyPacket);
    }
private:
    std::size_t id;
};

#endif /* NEWENEMY_PACKET_HPP */
