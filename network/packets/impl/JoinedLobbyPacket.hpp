/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** JoinedLobby packet
*/

#ifndef JOINED_LOBBY_PACKET_HPP
#define JOINED_LOBBY_PACKET_HPP

#include "network/packets/Packet.hpp"
#include <cstddef>
#include <iostream>
#include <memory>
#include <string>

class JoinedLobbyPacket : public Packet
{
public:
    JoinedLobbyPacket(std::string code = {}) :
        Packet(PacketId::JOINED_LOBBY_PACKET), code(code) {}

    enum PacketMode getMode() const {
        return PacketMode::TCP;
    }

    void serialize() {
        this->write(this->code);
    }

    void unserialize() {
        this->read(this->code);
    }

    const std::string getName() {
        return "JoinedLobbyPacket";
    }

    PacketDisplay display() const {
        return {"Code", code};
    }

    std::shared_ptr<Packet> clone() const {
        return make_copy(JoinedLobbyPacket);
    }

    std::string getCode() const { return this->code; }
private:
    std::string code;
};

#endif /* JOINED_LOBBY_PACKET_HPP */
