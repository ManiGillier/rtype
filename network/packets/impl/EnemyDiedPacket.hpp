/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** EnemyDied packet
*/

#ifndef ENEMYDIED_PACKET_HPP
#define ENEMYDIED_PACKET_HPP

#include "network/packets/Packet.hpp"
#include <cstddef>
#include <iostream>
#include <memory>

class EnemyDiedPacket : public Packet
{
public:
    EnemyDiedPacket(std::size_t id = 0) :
        Packet(PacketId::ENEMY_DIED), id(id) {}

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
        return "EnemyDiedPacket";
    }

    void display() {
        std::cout << "Id=" << this->id;
    }

    std::shared_ptr<Packet> clone() const {
        return make_copy(EnemyDiedPacket);
    }
    
    auto getEnemyId() const -> std::size_t { return this->id; }
private:
    std::size_t id;
};

#endif /* ENEMYDIED_PACKET_HPP */
