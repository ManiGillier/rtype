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
    #define BUFFER_SIZE 256
    #include "Packet.hpp"

class PacketReader {
public:
    PacketReader(int fd = -1);
    bool readPacket();
    bool createBuffer(void);
    std::queue<std::shared_ptr<Packet>> &getReceivedPackets();
    void setFd(int fd);
private:
    std::queue<std::shared_ptr<Packet>> receivedPackets; // les queues c'est banger :D (petits tricks)
    std::optional<std::shared_ptr<Packet>> currentPacket = std::nullopt;
    std::queue<uint8_t> readData;
    int _fd;
};

#endif /* !PACKETREADER_HPP_ */
