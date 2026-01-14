/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** Destroy entity packet
*/

#ifndef DESTROY_ENTITY_PACKET_HPP
#define DESTROY_ENTITY_PACKET_HPP

#include "network/packets/Packet.hpp"
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <memory>
#include <vector>

static std::ostream &operator<<(std::ostream &os, const std::vector<uint16_t> &v)
{
    os << "[";
    for (auto &id : v) {
        os << id << ", ";
    }
    os << "]";
    return os;
}

class DestroyEntityPacket : public Packet
{
public:
    DestroyEntityPacket(std::vector<uint16_t> ids = {}) :
        Packet(PacketId::DESTROY_ENTITY_PACKET), ids(ids) {}

    enum PacketMode getMode() const {
        return PacketMode::TCP;
    }

    void serialize() {
        this->write<uint16_t>(static_cast<uint16_t>(this->ids.size()));
        for (auto id : this->ids) {
            this->write<uint16_t>(id);
        }
    }

    void unserialize() {
        uint16_t size = 0;
        this->read<uint16_t>(size);
        this->ids.clear();
        this->ids.reserve(size);
        for (uint16_t index = 0; index < size; index++) {
            uint16_t data = 0;
            this->read<uint16_t>(data);
            this->ids.push_back(data);
        }
    }

    const std::string getName() {
        return "DestroyEntity";
    }

    PacketDisplay display() const {
        return {"Quantity", this->ids.size(), "Data", this->ids};
    }

    std::shared_ptr<Packet> clone() const {
        return make_copy(DestroyEntityPacket);
    }

    std::vector<uint16_t> getIds() const {
        return this->ids;
    }
private:
    std::vector<uint16_t> ids;
};

#endif /* DESTROY_ENTITY_PACKET_HPP */
