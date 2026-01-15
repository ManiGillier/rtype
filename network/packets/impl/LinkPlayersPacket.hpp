/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** LinkPlayers packet
*/

#ifndef LINK_PLAYERS_PACKET_HPP
#define LINK_PLAYERS_PACKET_HPP

#include "network/packets/Packet.hpp"
#include <cstddef>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

struct PlayerLink {
    std::string name;
    uint16_t id;
    uint16_t laserId;
};

inline std::string logData(std::vector<PlayerLink> data) {
    std::stringstream ss;

    ss << "[";
    for (auto &link : data) {
        ss << "{"
        << "Name=" << link.name << ","
        << "Id=" << link.id << ","
        << "LaserId=" << link.laserId
        << "};";
    }
    ss << "]";
    return ss.str();
}

class LinkPlayersPacket : public Packet
{
public:
    LinkPlayersPacket(std::vector<PlayerLink> data = {}) :
        Packet(PacketId::LINK_PLAYERS_PACKET), data(data) {}

    enum PacketMode getMode() const {
        return PacketMode::TCP;
    }

    void serialize() {
        this->write(static_cast<uint16_t>(this->data.size()));
        for (auto &d : this->data) {
            this->write(d.name);
            this->write(d.id);
            this->write(d.laserId);
        }
    }

    void unserialize() {
        this->data.clear();
        uint16_t size = 0;
        this->read(size);
        this->data.reserve(size);
        for (uint16_t i = 0; i < size; i++) {
            PlayerLink d;
            this->read(d.name);
            this->read(d.id);
            this->read(d.laserId);
            this->data.push_back(d);
        }
    }

    const std::string getName() {
        return "LinkPlayersPacket";
    }

    PacketDisplay display() const {
        return {"Quantity", this->data.size(), "Data", logData(this->data)};
    }

    std::shared_ptr<Packet> clone() const {
        return make_copy(LinkPlayersPacket);
    }

    std::vector<PlayerLink> getLinks() const {
        return this->data;
    }
private:
    std::vector<PlayerLink> data;
};

#endif /* LINK_PLAYERS_PACKET_HPP */
