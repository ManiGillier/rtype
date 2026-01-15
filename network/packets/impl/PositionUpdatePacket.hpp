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
#include <cstdint>
#include <iostream>
#include <memory>
#include <ostream>

struct PositionData {
    uint32_t id;
    float x;
    float y;
};

inline std::string logData(std::vector<PositionData> data)
{
    std::stringstream os;
    os << "[";
    for (auto &d : data) {
        os << "{";
        os << "ID=" << d.id << ",X=" << d.x << ",Y=" << d.y;
        os << "};";
    }
    os << "]";
    return os.str();
}

/*inline std::ostream &operator<<(std::ostream &os, std::vector<PositionData> &data)
{
    os << "[";
    for (auto &d : data) {
        os << "{";
        os << "ID=" << d.id << ",X=" << d.x << ",Y=" << d.y;
        os << "};";
    }
    os << "]";
    return os;
}
*/
class PositionUpdatePacket : public Packet
{
public:
    PositionUpdatePacket(std::vector<PositionData> data = {}) :
        Packet(PacketId::POSITION_UPDATE), data(data) {}

    enum PacketMode getMode() const override {
        return PacketMode::UDP;
    }

    void serialize() override {
        this->write<uint16_t>(static_cast<uint16_t>(data.size()));
        for (auto &d : data) {
            this->write(d.id);
            this->write(d.x);
            this->write(d.y);
        }
    }
    void unserialize() override {
        uint16_t size = 0;
        this->read(size);
        this->data.clear();
        this->data.reserve(size);
        for (uint16_t i = 0; i < size; i++) {
            PositionData d;
            this->read(d.id);
            this->read(d.x);
            this->read(d.y);
            this->data.push_back(d);
        }
    }

    const std::string getName() override {
        return "PositionUpdatePacket";
    }

    PacketDisplay display() const override {
        return {"Quantity", this->data.size(), "Data", logData(this->data)};
    }

    std::shared_ptr<Packet> clone() const override {
        return make_copy(PositionUpdatePacket);
    }

    std::vector<PositionData> getPositions() const { return this->data; }
private:
    std::vector<PositionData> data;
};

#endif /* POSITIONUPDATE_PACKET_HPP */
