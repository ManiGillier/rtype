/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** DeadPlayerPacket
*/

#ifndef DEADPLAYERPACKET_HPP_
    #define DEADPLAYERPACKET_HPP_

    #include "network/packets/Packet.hpp"

class PlayerDeadPacket : public Packet {
public:
    PlayerDeadPacket(int newPlayerCount=0, int whoDied=0) : Packet(PacketId::DEAD_PLAYER) {
        this->newPlayerCount = newPlayerCount;
        this->whoDied = whoDied;
    }
    void serialize() {
        this->writeInt(this->newPlayerCount);
        this->writeInt(this->whoDied);
    }

    void unserialize() {
        this->newPlayerCount = this->readInt(this->newPlayerCount);
        this->whoDied = this->readInt(this->whoDied);
    }

    int getPlayerCount() const {
        return this->newPlayerCount;
    }

    void setPlayerCount(int newPlayerCount) {
        this->newPlayerCount = newPlayerCount;
    }

    void setWhoDied(int whoDied) {
        this->whoDied = whoDied;
    }

    int getWhoDied() const {
        return this->whoDied;
    }

    enum PacketMode getMode() const {
        return PacketMode::TCP;
    }

    std::unique_ptr<Packet> clone() const {
        return make_copy(PlayerDeadPacket);
    }

    int getSize() const {
        return (int) sizeof(int) * 2;
    }

    const std::string getName() {
        return "PlayerDeadPacket";
    }

    void display() {
        std::cout << "PlayerCount = " << newPlayerCount << ", WhoDied=" <<
            this->whoDied;
    }
private:
    int newPlayerCount;
    int whoDied;
};

typedef PlayerDeadPacket PlayerDisconnectedPacket;

#endif /* !DEADPLAYERPACKET_HPP_ */
