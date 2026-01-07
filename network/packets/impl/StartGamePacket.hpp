/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** EnemyDied packet
*/

#ifndef STARTGMAE_PACKET_HPP
#define STARTGMAE_PACKET_HPP

#include "network/packets/Packet.hpp"
#include <cstddef>
#include <iostream>
#include <memory>

class StartGamePacket : public Packet
{
public:
    StartGamePacket() :
        Packet(PacketId::GAME_START_REQUEST) {}

    enum PacketMode getMode() const {
        return PacketMode::TCP;
    }

    void serialize() {
    }
    void unserialize() {
    }

    const std::string getName() {
        return "StartGamePacket";
    }

    PacketDisplay display() const {
        return {};
    }

    std::shared_ptr<Packet> clone() const {
        return make_copy(StartGamePacket);
    }
    
private:
};

#endif /* STARTGMAE_PACKET_HPP */
