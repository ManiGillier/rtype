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
        PacketManager(const PacketManager&) = delete;
        PacketManager& operator=(const PacketManager&) = delete;
        virtual ~PacketManager() = default;
        void registerPackets();
        std::optional<std::shared_ptr<Packet>> createPacketById(uint8_t id) const;
        bool hasPacketById(uint8_t id) const;

        static PacketManager& getInstance() {
            static PacketManager instance;
            return instance;
        }

    private:
        PacketManager() {
            this->registerPackets();
        }
        std::vector<std::shared_ptr<Packet>> packets;
};

#endif /* !PACKETMANAGER_HPP_ */
