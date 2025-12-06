/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** RequestStartPacket
*/

#ifndef REQUESTSTARTPACKET_HPP_
    #define REQUESTSTARTPACKET_HPP_

    #include "network/packets/Packet.hpp"

class StartRequestPacket : public Packet {
public:
    StartRequestPacket() : Packet(PacketId::REQUEST_START) {};
    void serialize() {};
    void unserialize() {};
    int getSize() const {
        return 0;
    }

    enum PacketMode getMode() const {
        return PacketMode::TCP;
    }

    std::unique_ptr<Packet> clone() const {
        return make_copy(StartRequestPacket);
    }

    const std::string getName() {
        return "StartRequestPacket";
    }

    void display() {
        std::cout << "None";
    }
};

#endif /* !REQUESTSTARTPACKET_HPP_ */
