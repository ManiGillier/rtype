/*
** EPITECH PROJECT, 2025
** rtype [WSL: Ubuntu-24.04]
** File description:
** CAuthentificationPacket
*/

#ifndef CAUTHENTIFICATIONPACKET_HPP_
    #define CAUTHENTIFICATIONPACKET_HPP_

    #include <network/packets/Packet.hpp>

class CAuthentificationPacket : public Packet {
public:
    CAuthentificationPacket(uint32_t uuid=0) : Packet(PacketId::C_AUTHENTICATION_PACKET) {
        this->uuid = uuid;
    }

    void serialize() {
        this->write(uuid);
    }

    void unserialize() {
        this->uuid = this->read(this->uuid);
    }

    enum PacketMode getMode() const {
    return PacketMode::UDP;
    }

    std::shared_ptr<Packet> clone() const {
        return make_copy(CAuthentificationPacket);
    }

    const std::string getName() {
        return "CAuthentificationPacket";
    }

    uint32_t getUUID() const {
        return this->uuid;
    }

    PacketDisplay display() const {
        return {"UUID", uuid};
    }

private:
    uint32_t uuid;
};

#endif /* !CAUTHENTIFICATIONPACKET_HPP_ */
