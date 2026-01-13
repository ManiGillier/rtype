/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** PacketReader
*/

#ifndef PACKETREADER_HPP_
    #define PACKETREADER_HPP_

    #include <optional>
    #include <queue>
    #define BUFFER_SIZE 8192
    #include "Packet.hpp"

class PacketReader {
public:
    PacketReader(int fd = -1,
        Packet::PacketMode mode=Packet::PacketMode::TCP);
    bool readPacket();
    bool createBuffer(void);
    std::queue<std::shared_ptr<Packet>> &getReceivedPackets();
    void setFd(int fd);
private:
    std::queue<std::shared_ptr<Packet>> receivedPackets; // les queues c'est banger :D (petits tricks)
    std::shared_ptr<Packet> currentPacket = nullptr;
    std::vector<uint8_t> readData;
    Packet::PacketMode mode;
    int _fd;
};

#endif /* !PACKETREADER_HPP_ */
