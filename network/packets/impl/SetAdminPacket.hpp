/*
** EPITECH PROJECT, 2026
** rtype [WSL: Ubuntu-24.04]
** File description:
** SetAdminPacket
*/

#ifndef SETADMINPACKET_HPP_
    #define SETADMINPACKET_HPP_

    #include <string>
    #include "network/packets/Packet.hpp"

class SetAdminPacket  : public Packet {
    public:
        SetAdminPacket() : Packet(PacketId::SET_ADMIN) {}

        enum PacketMode getMode() const {
            return PacketMode::TCP;
        }

        void serialize() {}

        void unserialize() {}

        const std::string getName() {
            return "SetAdmin";
        }

        PacketDisplay display() const {
            return {};
        }

        std::shared_ptr<Packet> clone() const {
            return make_copy(SetAdminPacket);
        }
};

#endif /* !SETADMINPACKET_HPP_ */
