/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** GameStartPacketRequest
*/

#ifndef GAMESTARTPACKET_REQUEST_HPP_
    #define GAMESTARTPACKET_REQUEST_HPP_

    #include "network/packets/Packet.hpp"

class GameStartPacketRequest : public Packet {
public:
    GameStartPacketRequest(std::size_t timestamp=0) : Packet(69) {
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
        return "GameStartPacketRequest";
    }

    enum PacketMode getMode() const {
        return PacketMode::TCP;
    }

    std::shared_ptr<Packet> clone() const {
        return make_copy(GameStartPacketRequest);
    }

    void display() {
        std::cout << "Timestamp=" << timestamp;
    }

private:
    std::size_t timestamp;
};

#endif /* !GAMESTARTPACKET_REQUEST_HPP_ */
