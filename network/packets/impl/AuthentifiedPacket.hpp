/*
** EPITECH PROJECT, 2025
** rtype [WSL: Ubuntu-24.04]
** File description:
** AuthentifiedPacket
*/

#ifndef AUTHENTIFIEDPACKET_HPP_
    #define AUTHENTIFIEDPACKET_HPP_

    #include <network/packets/Packet.hpp>

class AuthentifiedPacket : public Packet {
public:
    AuthentifiedPacket() : Packet(PacketId::AUTHENTIFIED_PACKET) {};
    void serialize() {};
    void unserialize() {};
    int getSize() const {
        return 0;
    }

    enum PacketMode getMode() const {
        return PacketMode::TCP;
    }

    std::shared_ptr<Packet> clone() const {
        return make_copy(AuthentifiedPacket);
    }

    const std::string getName() {
        return "AuthentifiedPacket";
    }

    void display() {
        std::cout << "None";
    }
};

#endif /* !AUTHENTIFIEDPACKET_HPP_ */
