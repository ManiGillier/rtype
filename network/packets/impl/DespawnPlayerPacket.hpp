/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** DespawnPlayer packet
*/

#ifndef DESPAWNPLAYER_PACKET_HPP
#define DESPAWNPLAYER_PACKET_HPP

#include "network/packets/Packet.hpp"
#include <cstddef>
#include <iostream>
#include <memory>

class DespawnPlayerPacket : public Packet
{
public:
    DespawnPlayerPacket(std::size_t id = 0) :
        Packet(PacketId::DESPAWN_PLAYER), id(id) {}

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
        return "DespawnPlayerPacket";
    }

    PacketDisplay display() const {
        return {"Id", this->id};
    }

    std::shared_ptr<Packet> clone() const {
        return make_copy(DespawnPlayerPacket);
    }
    auto getPlayerId() const -> std::size_t { return this->id; }
private:
    std::size_t id;
};

#endif /* DESPAWNPLAYER_PACKET_HPP */
