/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** PlayerHit packet
*/

#ifndef TESTPACKET_HPP
#define TESTPACKET_HPP

#include "network/packets/Packet.hpp"
#include <cstddef>
#include <iostream>
#include <memory>

class TestPacket : public Packet
{
public:
    TestPacket(std::string testString="") :
        Packet(PacketId::TEST_PACKET), testString(testString) {}

    enum PacketMode getMode() const {
        return PacketMode::TCP;
    }

    void serialize() {
        this->write(testString);
    }

    void unserialize() {
        this->read(testString);
    }

    const std::string getName() {
        return "TestPacket";
    }

    void display() {
        std::cout << "TestString=" << this->testString;
    }

    std::shared_ptr<Packet> clone() const {
        return make_copy(TestPacket);
    }
private:
    std::string testString;
};

#endif /* TESTPACKET_HPP */
