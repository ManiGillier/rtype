/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** PlayerId packet
*/

#ifndef PLAYERID_PACKET_HPP
#define PLAYERID_PACKET_HPP

#include "network/packets/Packet.hpp"
#include <cstddef>
#include <iostream>
#include <memory>

class PlayerIdPacket : public Packet
{
public:
    PlayerIdPacket(std::size_t id = 0) :
        Packet(PacketId::PLAYER_ID), id(id) {}

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
        return "PlayerIdPacket";
    }

    PacketDisplay display() const {
        return {"Id", this->id};
    }

    std::shared_ptr<Packet> clone() const {
        return make_copy(PlayerIdPacket);
    }

    auto getId() const -> std::size_t { return this->id; }
private:
    std::size_t id;
};

#endif /* PLAYERID_PACKET_HPP */
