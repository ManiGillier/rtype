/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** Time now packet
*/

#ifndef TIME_NOW_PACKET_HPP
#define TIME_NOW_PACKET_HPP

#include "network/packets/Packet.hpp"
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <memory>

class TimeNowPacket : public Packet
{
public:
    TimeNowPacket(uint32_t now) :
        Packet(PacketId::TIME_NOW_PACKET), now(now) {}

    enum PacketMode getMode() const {
        return PacketMode::TCP;
    }

    void serialize() {
        this->write(now);
    }
    void unserialize() {
        this->read(now);
    }

    const std::string getName() {
        return "TimeNowPacket";
    }

    PacketDisplay display() const {
        return {"Now", this->now};
    }

    std::shared_ptr<Packet> clone() const {
        return make_copy(TimeNowPacket);
    }

    auto getPlayerId() const -> std::size_t { return this->now; }
private:
    uint32_t now;
};

#endif /* TIME_NOW_PACKET_HPP */
