/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** CreatePrivateLobby packet
*/

#ifndef CREATE_PRIVATE_LOBBY_PACKET_HPP
#define CREATE_PRIVATE_LOBBY_PACKET_HPP

#include "network/packets/Packet.hpp"
#include <cstddef>
#include <iostream>
#include <memory>

class CreatePrivateLobbyPacket : public Packet
{
public:
    CreatePrivateLobbyPacket() :
        Packet(PacketId::CREATE_PRIVATE_LOBBY_PACKET) {}

    enum PacketMode getMode() const {
        return PacketMode::TCP;
    }

    void serialize() {
    }

    void unserialize() {
    }

    const std::string getName() {
        return "CreatePrivateLobbyPacket";
    }

    PacketDisplay display() const {
        return {};
    }

    std::shared_ptr<Packet> clone() const {
        return make_copy(CreatePrivateLobbyPacket);
    }
private:
};

#endif /* CREATE_PRIVATE_LOBBY_PACKET_HPP */
