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
        this->write(inputs);
    }
    void unserialize() {
        this->read(inputs);
    }

    auto getSize() const -> int { return sizeof(ClientInputs); }

    const std::string getName() {
        return "ClientInputsPacket";
    }

    void display() {
        std::cout << "Inputs={";
        if (this->inputs.value.left) std::cout << "LEFT,";
        if (this->inputs.value.right) std::cout << "RIGHT,";
        if (this->inputs.value.up) std::cout << "UP,";
        if (this->inputs.value.down) std::cout << "DOWN,";
        if (this->inputs.value.shoot) std::cout << "SHOOT,";
        std::cout << "}";
    }

    std::shared_ptr<Packet> clone() const {
        return std::make_shared<ClientInputsPacket>(*this);
    }

    auto getInputs() const -> ClientInputs { return this->inputs; }
 private:
    ClientInputs inputs;
};

#endif /* CLIENTINPUTS_PACKET_HPP */
