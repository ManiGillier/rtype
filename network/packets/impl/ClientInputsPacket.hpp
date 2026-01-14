/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** ClientInputs packet
*/

#ifndef CLIENTINPUTS_PACKET_HPP
#define CLIENTINPUTS_PACKET_HPP

#include "network/packets/Packet.hpp"
#include <cstdint>
#include <iostream>
#include <memory>

union ClientInputs {
    std::uint8_t byte;
    struct value {
        std::uint8_t left : 1;
        std::uint8_t right : 1;
        std::uint8_t up : 1;
        std::uint8_t down : 1;
        std::uint8_t shoot : 1;
        std::uint8_t : 3;
    } value;
};

class ClientInputsPacket : public Packet
{
public:
    ClientInputsPacket(ClientInputs inputs = {0}) :
        Packet(PacketId::CLIENT_INPUTS), inputs(inputs) {}

    enum PacketMode getMode() const {
        return PacketMode::UDP;
    }

    void serialize() {
        this->write(inputs.byte);
    }
    void unserialize() {
        this->read(inputs.byte);
    }

    const std::string getName() {
        return "ClientInputsPacket";
    }

    PacketDisplay display() const {
        return {"Inputs", this->inputs};
    }

    std::shared_ptr<Packet> clone() const {
        return std::make_shared<ClientInputsPacket>(*this);
    }

    auto getInputs() const -> ClientInputs { return this->inputs; }
 private:
    ClientInputs inputs;
};

inline std::ostream& operator<<(std::ostream &out, ClientInputs const &inputs)
{
    if (inputs.value.left)  out << "LEFT,";
    if (inputs.value.right) out << "RIGHT,";
    if (inputs.value.up)    out << "UP,";
    if (inputs.value.down)  out << "DOWN,";
    if (inputs.value.shoot) out << "SHOOT,";
    return out;
}

#endif /* CLIENTINPUTS_PACKET_HPP */
