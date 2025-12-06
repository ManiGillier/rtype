/*
** EPITECH PROJECT, 2025
** jetpack [WSL: Ubuntu-24.04]
** File description:
** PlayerLostPacket
*/

#ifndef PLAYERLOSTPACKET_HPP_
    #define PLAYERLOSTPACKET_HPP_

    #include "network/packets/Packet.hpp"

class PlayerLostPacket : public Packet {
public:
    PlayerLostPacket() : Packet(PacketId::PLAYER_LOST) {};
    void serialize() {};
    void unserialize() {};
    int getSize() const {
        return 0;
    }
    const std::string getName() {
        return "PlayerLostPacket";
    }

    enum PacketMode getMode() const {
        return PacketMode::TCP;
    }

    std::unique_ptr<Packet> clone() const {
        return make_copy(PlayerLostPacket);
    }

    void display() {
        std::cout << "None";
    }
};

#endif /* !PLAYERLOSTPACKET_HPP_ */
