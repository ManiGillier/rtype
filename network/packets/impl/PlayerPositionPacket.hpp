/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** PlayerPositionPacket
*/

#ifndef PLAYERPOSITIONPACKET_HPP_
    #define PLAYERPOSITIONPACKET_HPP_

    #include "network/packets/Packet.hpp"

class PlayerPositionPacket : public Packet {
public:
    PlayerPositionPacket(double position=0.0) : Packet(PacketId::UPDATE_POSITION) {
        this->position = position;
    }

    int getSize() const {
        return DOUBLE_SIZE;
    }

    void setPosition(double position) {
        this->position = position;
    }

    double getPosition() const {
        return this->position;
    }

    void serialize() {
        this->writeDouble(position);
    }

    void unserialize() {
        this->position = this->readDouble(position);
    }

    const std::string getName() {
        return "PlayerPositionPacket";
    }

    void display() {
        std::cout << "PositionY=" << this->position;
    }

private:
    double position;
};

#endif /* !PLAYERPOSITIONPACKET_HPP_ */
