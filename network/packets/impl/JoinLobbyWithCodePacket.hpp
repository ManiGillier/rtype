/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** JoinLobbyWithCode packet
*/

#ifndef JOIN_LOBBY_WITH_CODE_PACKET_HPP
#define JOIN_LOBBY_WITH_CODE_PACKET_HPP

#include "network/packets/Packet.hpp"
#include <cstddef>
#include <iostream>
#include <memory>
#include <string>

class JoinLobbyWithCodePacket : public Packet
{
public:
    JoinLobbyWithCodePacket(std::string code = {}) :
        Packet(PacketId::JOIN_LOBBY_WITH_CODE_PACKET), code(code) {}

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
        return "JoinLobbyWithCodePacket";
    }

    PacketDisplay display() const {
        return {"Code", code};
    }

    std::shared_ptr<Packet> clone() const {
        return make_copy(JoinLobbyWithCodePacket);
    }

    std::string getCode() const {
        return this->code;
    }
private:
    std::string code;
};

#endif /* JOIN_LOBBY_WITH_CODE_PACKET_HPP */
