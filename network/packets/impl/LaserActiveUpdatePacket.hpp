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
#include <cstdint>
#include <iostream>
#include <memory>
#include <ostream>
#include <vector>

struct LaserData {
    uint32_t id;
    uint8_t active;
    float length;
};

inline std::ostream &operator<<(std::ostream &os, const std::vector<LaserData> &d)
{
    os << "[";
    for (auto data : d) {
        os << "{" << "ID=" << data.id << ",ACTIVE=" << (data.active
            ? "TRUE" : "FALSE")
            << ",LENGTH=" << data.length << "};";
    }
    os << "]";
    return os;
}

class LaserActiveUpdatePacket : public Packet
{
public:
    LaserActiveUpdatePacket(std::vector<LaserData> data = {}) :
        Packet(PacketId::LASER_ACTIVE_UPDATE), data(data) {}

    enum PacketMode getMode() const override {
        return PacketMode::UDP;
    }

    void serialize() override {
        this->write(static_cast<uint16_t>(this->data.size()));
        for (auto &d : this->data) {
            this->write(d.id);
            this->write(d.active);
            this->write(d.length);
        }
    }
    void unserialize()override {
        this->data.clear();
        uint16_t size = 0;
        this->read(size);
        this->data.reserve(size);
        for (uint16_t i = 0; i < size; i++) {
            LaserData laser;
            this->read(laser.id);
            this->read(laser.active);
            this->read(laser.length);
            this->data.push_back(laser);
        }
    }

    const std::string getName() override {
        return "LaserActiveUpdatePacket";
    }

    PacketDisplay display() const override {
        return {"Quantity", this->data.size(), "Data", this->data};
    }

    std::shared_ptr<Packet> clone() const override {
        return make_copy(LaserActiveUpdatePacket);
    }

    std::vector<LaserData> getLaserData() const {
        return this->data;
    }
private:
    std::vector<LaserData> data;
};

#endif /* LASERACTIVEUPDATE_PACKET_HPP */
