/*
** EPITECH PROJECT, 2025
** rtype [WSL: Ubuntu-24.04]
** File description:
** SAuthentificationPacket
*/

#ifndef SAUTHENTIFICATIONPACKET_HPP_
    #define SAUTHENTIFICATIONPACKET_HPP_

    #include <network/packets/Packet.hpp>
    #include <atomic>

class SAuthentificationPacket : public Packet {
public:

    SAuthentificationPacket(uint32_t uuid=0) : Packet(PacketId::S_AUTHENTICATION_PACKET) {
        this->uuid = uuid;
    }

    void serialize() {
        this->write(uuid);
    }

    void unserialize() {
        this->uuid = this->read(this->uuid);
    }

    int getSize() const {
        return (int) sizeof(uint32_t);
    }

    enum PacketMode getMode() const {
        return PacketMode::TCP;
    }

    std::shared_ptr<Packet> clone() const {
        return make_copy(SAuthentificationPacket);
    }

    const std::string getName() {
        return "SAuthentificationPacket";
    }

    void setUUID(uint32_t uuid) {
        this->uuid = uuid;
    }

    uint32_t getUUID() const {
        return this->uuid;
    }

    void display() {
        std::cout << "UUID=" << uuid;
    }

private:
    uint32_t uuid;
};

#endif /* !SAUTHENTIFICATIONPACKET_HPP_ */
