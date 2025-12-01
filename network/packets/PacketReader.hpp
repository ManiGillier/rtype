/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** PacketReader
*/

#ifndef PACKETREADER_HPP_
    #define PACKETREADER_HPP_

    #include <queue>
    #define BUFFER_SIZE 256
    #include "Packet.hpp"

class PacketReader {
public:
    PacketReader(int fd);
    bool readPacket();
    bool createBuffer(void);
    std::queue<Packet *> &getReceivedPackets();
    inline static bool shouldLog = false;
private:
    Packet *buildPacket(char packetId);
    std::queue<Packet *> receivedPackets; // les queues c'est banger :D (petits tricks)
    Packet *currentPacket = nullptr;
    std::queue<uint8_t> readData;
    int readBytes = 0;
    int _fd;
};

#endif /* !PACKETREADER_HPP_ */
