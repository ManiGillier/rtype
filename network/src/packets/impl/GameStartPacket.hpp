/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** GameStartPacket
*/

#ifndef GAMESTARTPACKET_HPP_
    #define GAMESTARTPACKET_HPP_

    #include "Packet.hpp"

class GameStartPacket : public Packet {
public:
    GameStartPacket(std::size_t timestamp=0) : Packet(PacketId::START_GAME) {
        this->timestamp = timestamp;
    }

    void serialize() {
        this->write(timestamp);
    }

    void unserialize() {
        this->timestamp = read(this->timestamp);
    }

    std::size_t getTimestamp() const {
        return this->timestamp;
    }

    void setTimestamp(std::size_t timestamp) {
        this->timestamp = timestamp;
    }

    int getSize() const {
        return (int) sizeof(std::size_t);
    }

    const std::string getName() {
        return "GameStartPacket";
    }

    void display() {
        std::cout << "Timestamp=" << timestamp;
    }

private:
    std::size_t timestamp;
};

#endif /* !GAMESTARTPACKET_HPP_ */
