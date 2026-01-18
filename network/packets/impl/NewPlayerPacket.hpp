/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** NewPlayer packet
*/

#ifndef NEWPLAYER_PACKET_HPP
#define NEWPLAYER_PACKET_HPP

#include "network/packets/Packet.hpp"
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <memory>

/*static std::ostream &operator<<(std::ostream &os,
    const std::vector<std::string> &data)
{
    os << "[";
    for (auto &d : data) {
        os << "\"" << d << "\", ";
    }
    os << "]";
    return os;
}
*/
class NewPlayerPacket : public Packet
{
public:
    NewPlayerPacket(std::vector<std::string> usernames = {}) :
        Packet(PacketId::NEW_PLAYER), usernames(usernames) {}

    enum PacketMode getMode() const {
        return PacketMode::TCP;
    }

    void serialize() {
        this->write(static_cast<uint16_t>(this->usernames.size()));
        for (auto &username : this->usernames) {
            this->write(username);
        }
    }
    void unserialize() {
        uint16_t size = 0;
        this->read(size);
        this->usernames.clear();
        this->usernames.reserve(size);
        for (uint16_t i = 0; i < size; i++) {
            std::string username = {};
            this->read(username);
            this->usernames.push_back(username);
        }
    }

    const std::string getName() {
        return "NewPlayerPacket";
    }

    PacketDisplay display() const {
        return {"Quantity", this->usernames.size()};
    }

    std::shared_ptr<Packet> clone() const {
        return make_copy(NewPlayerPacket);
    }

    std::vector<std::string> getUsernames() const {
        return this->usernames;
    }
private:
    std::vector<std::string> usernames;
};

#endif /* NEWPLAYER_PACKET_HPP */
