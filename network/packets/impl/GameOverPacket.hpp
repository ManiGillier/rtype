/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** GameOver packet
*/

#ifndef GAMEOVER_PACKET_HPP
#define GAMEOVER_PACKET_HPP

#include "network/packets/Packet.hpp"
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <memory>

enum EndGameState : std::uint8_t {
      WIN = 1,
      LOST
};

static std::string egsToString(enum EndGameState egs)
{
    switch (egs) {
        case WIN:
            return "WIN";
        case LOST:
            return "LOST";
    }
    return "ERROR";
}

class GameOverPacket : public Packet
{
public:
    GameOverPacket(enum EndGameState egs = LOST) :
        Packet(PacketId::GAME_OVER), egs(egs) {}

    enum PacketMode getMode() const {
        return PacketMode::TCP;
    }

    void serialize() {
        this->write(egs);
    }
    void unserialize() {
        this->read(egs);
    }
    auto getSize() const -> int { return sizeof(enum EndGameState); }

    const std::string getName() {
        return "GameOverPacket";
    }

    void display() {
        std::cout << "EndGameState=" << egsToString(egs);
    }

    std::shared_ptr<Packet> clone() const {
        return make_copy(GameOverPacket);
    }
private:
    enum EndGameState egs;
};

#endif /* GAMEOVER_PACKET_HPP */
