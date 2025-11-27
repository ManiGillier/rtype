/*
** EPITECH PROJECT, 2025
** jetpack [WSL: Ubuntu-24.04]
** File description:
** PlayerWonPacket
*/

#ifndef PLAYERWONPACKET_HPP_
    #define PLAYERWONPACKET_HPP_

    #include "Packet.hpp"

class PlayerWonPacket : public Packet {
public:
    PlayerWonPacket() : Packet(PacketId::PLAYER_WON) {};
    void serialize() {};
    void unserialize() {};
    int getSize() const {
        return 0;
    }

    const std::string getName() {
        return "PlayerWonPacket";
    }

    void display() {
        std::cout << "None";
    }
};

#endif /* !PLAYERWONPACKET_HPP_ */
