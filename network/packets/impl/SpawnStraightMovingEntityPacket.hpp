/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** Spawn straight moving entity packet
*/

#ifndef SPAWN_STRAIGHT_MOVING_ENTITY_PACKET_HPP
#define SPAWN_STRAIGHT_MOVING_ENTITY_PACKET_HPP

#include "network/packets/Packet.hpp"
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <memory>
#include <ostream>
#include <vector>

struct StraightMovingEntity {
    uint16_t id;
    uint16_t pos_x;
    uint16_t pos_y;
    uint16_t vel_x;
    uint16_t vel_y;
    uint8_t hitbox_x;
    uint8_t hitbox_y;
    uint32_t ms_time;
};

std::ostream &operator<<(std::ostream &os,
                         const std::vector<StraightMovingEntity> &data)
{
    for (auto &d : data) {
        os << "Id=" << d.id << "{ "
            << "Pos={" << d.pos_x << "," << d.pos_y << "} "
            << "Vel={" << d.vel_x << "," << d.vel_y << "} "
            << "Hitbix ={" << d.hitbox_x << "," << d.hitbox_y << "} "
            << "Timestamp=" << d.ms_time << " } ; ";
    }
    return os;
}

class SpawnStraightMovingEntityPacket : public Packet
{
public:
    SpawnStraightMovingEntityPacket(std::vector<StraightMovingEntity> &data)
    : Packet(SPAWN_STRAIGHT_MOVING_ENTITY_PACKET), data(data) {}

    enum PacketMode getMode() const {
        return PacketMode::TCP;
    }

    void serialize() {
        this->write(static_cast<uint16_t>(this->data.size()));
        for (auto &d : this->data) {
            this->write(d.id);
            this->write(d.pos_x);
            this->write(d.pos_y);
            this->write(d.vel_x);
            this->write(d.vel_y);
            this->write(d.hitbox_x);
            this->write(d.hitbox_y);
            this->write(d.ms_time);
        }
    }

    void unserialize() {
        this->data.clear();
        uint16_t size = 0;
        this->read(size);
        this->data.reserve(size);
        for (uint16_t i = 0; i < size; i++) {
            StraightMovingEntity move;
            this->read(move.id);
            this->read(move.pos_x);
            this->read(move.pos_y);
            this->read(move.vel_x);
            this->read(move.vel_y);
            this->read(move.hitbox_x);
            this->read(move.hitbox_y);
            this->read(move.ms_time);
            this->data.push_back(move);
        }
    }

    const std::string getName() {
        return "SpawnStraightMovingEntityPacket";
    }

    PacketDisplay display() const {
        return {"Quantity", this->data.size(), "All data", this->data};
    }

    std::vector<StraightMovingEntity> getMovingEntities() {
        return this->data;
    }

    std::shared_ptr<Packet> clone() const {
        return make_copy(SpawnStraightMovingEntityPacket);
    }
private:
    std::vector<StraightMovingEntity> data;
};

#endif /* SPAWN_STRAIGHT_MOVING_ENTITY_PACKET_HPP */
