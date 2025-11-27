/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** JoinPlayerPacket
*/

#ifndef JOINPLAYERPACKET_HPP_
    #define JOINPLAYERPACKET_HPP_

    #include "Packet.hpp"

class PlayerJoinPacket : public Packet {
public:
    PlayerJoinPacket(int newPlayerCount=0) : Packet(PacketId::BORN_PLAYER) {
        this->newPlayerCount = newPlayerCount;
    }

    void serialize() {
        this->writeInt(this->newPlayerCount);  
    }

    void unserialize() {
        this->newPlayerCount = this->readInt(this->newPlayerCount);
    }

    int getPlayerCount() const {
        return this->newPlayerCount;
    }
        
    void setPlayerCount(int newPlayerCount) {
        this->newPlayerCount = newPlayerCount;
    }

    int getSize() const {
        return (int) sizeof(int);
    }

    const std::string getName() {
        return "PlayerJoinPacket";
    }

    void display() {
        std::cout << "PlayerCount = " << newPlayerCount;
    }
private:
    int newPlayerCount;
};

#endif /* !JOINPLAYERPACKET_HPP_ */
