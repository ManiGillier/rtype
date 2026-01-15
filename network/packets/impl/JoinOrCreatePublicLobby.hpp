/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** JoinOrCreatePublicLobby packet
*/

#ifndef JOIN_OR_CREATE_PUBLIC_LOBBY_PACKET_HPP
#define JOIN_OR_CREATE_PUBLIC_LOBBY_PACKET_HPP

#include "network/packets/Packet.hpp"
#include <cstddef>
#include <iostream>
#include <memory>

class JoinOrCreatePublicLobbyPacket : public Packet
{
public:
    JoinOrCreatePublicLobbyPacket() :
        Packet(PacketId::JOIN_OR_CREATE_PUBLIC_LOBBY_PACKET) {}

    enum PacketMode getMode() const {
        return PacketMode::TCP;
    }

    void serialize() {
    }

    void unserialize() {
    }

    const std::string getName() {
        return "JoinOrCreatePublicLobbyPacket";
    }

    PacketDisplay display() const {
        return {};
    }

    std::shared_ptr<Packet> clone() const {
        return make_copy(JoinOrCreatePublicLobbyPacket);
    }
private:
};

#endif /* JOIN_OR_CREATE_PUBLIC_LOBBY_PACKET_HPP */
