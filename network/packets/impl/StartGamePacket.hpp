/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** EnemyDied packet
*/

#ifndef STARTGMAE_PACKET_HPP
#define STARTGMAE_PACKET_HPP

#include "network/packets/Packet.hpp"
#include <cstdint>
#include <memory>

struct GameStartConfig {
    uint8_t difficuly : 4;
    uint8_t lives : 4;
};

union GameStartConfigUnion {
    GameStartConfig config;
    uint8_t data;
};

class StartGamePacket : public Packet
{
public:
    StartGamePacket(GameStartConfig config = {0, 0}) :
        Packet(PacketId::GAME_START_REQUEST), config({.config = config}) {}

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
        return "StartGamePacket";
    }

    PacketDisplay display() const {
        return {
            "Difficulty", (int) this->config.config.difficuly,
            "Lives", (int) this->config.config.lives
        };
    }

    std::shared_ptr<Packet> clone() const {
        return make_copy(StartGamePacket);
    }

    GameStartConfig getConfig() const {
        return this->config.config;
    }
private:
    GameStartConfigUnion config;
};

#endif /* STARTGMAE_PACKET_HPP */
