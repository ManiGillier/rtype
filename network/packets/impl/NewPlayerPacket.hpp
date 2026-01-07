/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** NewPlayer packet
*/

#ifndef NEWPLAYER_PACKET_HPP
#define NEWPLAYER_PACKET_HPP

#include "network/packets/Packet.hpp"
#include <cstddef>
#include <iostream>
#include <memory>

class NewPlayerPacket : public Packet
{
public:
    NewPlayerPacket(std::size_t id = 0, std::size_t laser_id = 0) :
        Packet(PacketId::NEW_PLAYER), id(id), laser_id(laser_id) {}

    enum PacketMode getMode() const {
        return PacketMode::TCP;
    }

    void serialize() {
        this->write(id);
        this->write(laser_id);
    }
    void unserialize() {
        this->read(id);
        this->read(laser_id);
    }

    const std::string getName() {
        return "NewPlayerPacket";
    }

    PacketDisplay display() const {
        return {"playerId", this->id, "laserId", this->laser_id};
    }

    std::shared_ptr<Packet> clone() const {
        return make_copy(NewPlayerPacket);
    }

    auto getPlayerId() const -> std::size_t { return this->id; }
    auto getLaserId() const -> std::size_t { return this->laser_id; }
private:
    std::size_t id;
    std::size_t laser_id;
};

#endif /* NEWPLAYER_PACKET_HPP */
