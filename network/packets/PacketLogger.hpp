/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** PacketLogger
*/

#ifndef PACKETLOGGER_HPP_
    #define PACKETLOGGER_HPP_

    #include "Packet.hpp"
    #include "network/logger/Logger.hpp"

class PacketLogger {
    public:
        enum PacketMethod {RECEIVED, SENT};

        static void logPacket(const std::shared_ptr<Packet> &packet, PacketMethod method, int fd, uint16_t sequenceNum=0) {
            if (!Logger::shouldLog)
                return;
            LOG((method == RECEIVED ? "Received" : "Sent") <<
                " packet " << packet->getName() << " with ID " << (int) packet->getId() << " and data {");
            packet->display().display();
            if (packet->getMode() == Packet::UDP && sequenceNum != 0)
                std::cout << "} and icmp_seq=" << sequenceNum << (method == RECEIVED ? " from" : " to");
            else
                std::cout << "}" << (method == RECEIVED ? " from" : " to");
            std::cout << " socket " << fd << std::endl;
        }
};

#endif /* !PACKETLOGGER_HPP_ */
