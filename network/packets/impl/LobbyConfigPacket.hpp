/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** EnemyDied packet
*/

#ifndef LOBBY_CONFIG_PACKET_HPP
#define LOBBY_CONFIG_PACKET_HPP

#include "network/packets/Packet.hpp"
#include <cstdint>
#include <memory>

#include "StartGamePacket.hpp"

class LobbyConfigPacket : public Packet
{
public:
    LobbyConfigPacket(GameStartConfig config = {0, 0}) :
        Packet(PacketId::LOBBY_CONFIG_PACKET), config({.config = config}) {}

    enum PacketMode getMode() const {
        return PacketMode::TCP;
    }

    void serialize() {
        this->write(config.data);
    }
    void unserialize() {
        this->read(config.data);
    }

    const std::string getName() {
        return "LobbyConfigPacket";
    }

    PacketDisplay display() const {
        return {
            "Difficulty", (int) this->config.config.difficuly,
            "Lives", (int) this->config.config.lives
        };
    }

    std::shared_ptr<Packet> clone() const {
        return make_copy(LobbyConfigPacket);
    }

    GameStartConfig getConfig() const {
        return this->config.config;
    }
private:
    GameStartConfigUnion config;
};

#endif /* LOBBY_CONFIG_PACKET_HPP */
