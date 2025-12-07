/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** PacketSender
*/

#ifndef PACKETSENDER_HPP_
    #define PACKETSENDER_HPP_

    #include "Packet.hpp"
    #include <queue>

class PacketSender {
public:
    PacketSender(int fd);
    void sendPackets(std::queue<Packet *> packets);
    void sendPacket(Packet *packet);
    void writePackets();
    std::queue<Packet *> getPackets() const;
private:
    int _fd;
    std::queue<Packet *> packets;
};

#endif /* !PACKETSENDER_HPP_ */
