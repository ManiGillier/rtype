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

        static void logPacket(Packet *packet, PacketMethod method, int fd) {
            LOG << (method == RECEIVED ? "Received" : "Sent") <<
                " packet " << packet->getName() << " with ID " << (int) packet->getId() << " and data {";
            packet->display();
            std::cout << "}" << (method == RECEIVED ? " from" : " to")
            << " socket " << fd << std::endl;
        }
};

#endif /* !PACKETLOGGER_HPP_ */
