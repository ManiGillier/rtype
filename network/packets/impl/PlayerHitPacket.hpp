/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** PlayerHit packet
*/

#ifndef PLAYERHIT_PACKET_HPP
#define PLAYERHIT_PACKET_HPP

#include "network/packets/Packet.hpp"
#include <cstddef>
#include <iostream>
#include <memory>

class PlayerHitPacket : public Packet
{
public:
    PlayerHitPacket() :
        Packet(PacketId::PLAYER_HIT) {}

    enum PacketMode getMode() const {
        return PacketMode::TCP;
    }

    void serialize() {
    }
    void unserialize() {
    }

    const std::string getName() {
        return "PlayerHitPacket";
    }

    PacketDisplay display() const {
        return {};
    }

    std::shared_ptr<Packet> clone() const {
        return make_copy(PlayerHitPacket);
    }
private:
};

#endif /* PLAYERHIT_PACKET_HPP */
