/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** GhostPlayerPositionPacket
*/

#ifndef GHOSTPLAYERPOSITIONPACKET_HPP_
    #define GHOSTPLAYERPOSITIONPACKET_HPP_

    #include "network/packets/Packet.hpp"

class GhostPlayerPositionPacket : public Packet {
public:
    GhostPlayerPositionPacket(int id = 0, double position=0.0)
        : Packet(PacketId::GHOST_PLAYER_POSITION) {
        this->id = id;
        this->position = position;
    }

    int getSize() const {
        return INT_SIZE + DOUBLE_SIZE;
    }

    void setPlayerID(int id) {
        this->id = id;
    }

    int getPlayerID() const {
        return this->id;
    }

    void setPosition(double position) {
        this->position = position;
    }

    double getPosition() const {
        return this->position;
    }

    void serialize() {
        this->writeInt(id);
        this->writeDouble(position);
    }

    void unserialize() {
        this->id = this->readInt(id);
        this->position = this->readDouble(position);
    }

    const std::string getName() {
        return "GhostPlayerPositionPacket";
    }

    void display() {
        std::cout << "PlayerID=" << this->id
                  << ", PositionY=" << this->position;
    }

private:
    int id;
    double position;
};

#endif /* !GHOSTPLAYERPOSITIONPACKET_HPP_ */
