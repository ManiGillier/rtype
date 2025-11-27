/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** RequestStartPacket
*/

#ifndef REQUESTSTARTPACKET_HPP_
    #define REQUESTSTARTPACKET_HPP_

    #include "Packet.hpp"

class StartRequestPacket : public Packet {
public:
    StartRequestPacket() : Packet(PacketId::REQUEST_START) {};
    void serialize() {};
    void unserialize() {};
    int getSize() const {
        return 0;
    }

    const std::string getName() {
        return "StartRequestPacket";
    }

    void display() {
        std::cout << "None";
    }
};

#endif /* !REQUESTSTARTPACKET_HPP_ */
