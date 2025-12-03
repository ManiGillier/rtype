/*
** EPITECH PROJECT, 2025
** rtype [WSL: Ubuntu-24.04]
** File description:
** PacketManager
*/

#ifndef PACKETMANAGER_HPP_
    #define PACKETMANAGER_HPP_

    #include <iostream>
    #include <vector>
    #include <memory>
    #include <optional>
    #include "Packet.hpp"

class PacketManager {
    public:
        void registerPackets();
        std::optional<std::unique_ptr<Packet>> getPacketById(uint8_t id) const;
        bool hasPacketById(uint8_t id) const;
    private:
        std::vector<std::unique_ptr<Packet>> packets;
};

#endif /* !PACKETMANAGER_HPP_ */
