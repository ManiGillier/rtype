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
    PacketSender(int fd = -1);
    void sendPacket(std::shared_ptr<Packet> packet);
    void writePackets();
    std::queue<std::shared_ptr<Packet>> getPackets() const;
    void setFd(int fd);
    bool shouldSend() const;
private:
    int _fd;
    std::vector<uint8_t> dataQueue;
};

#endif /* !PACKETSENDER_HPP_ */
