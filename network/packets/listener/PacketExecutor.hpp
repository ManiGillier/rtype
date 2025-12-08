/*
** EPITECH PROJECT, 2025
** rtype [WSL: Ubuntu-24.04]
** File description:
** PacketExecutor
*/

#ifndef PACKETEXECUTOR_HPP_
    #define PACKETEXECUTOR_HPP_

    #include "Server.hpp"
    // TODO: Fix that shit what the fuck.
    #include "../Packet.hpp"

class PacketExecutor {
    public:
        // Server and clients are both null if its a Client Executor
        virtual bool executePacket(Server *server, Client *cl, Packet *packet) = 0;
        virtual ~PacketExecutor() = default;
        virtual int getPacketId() const = 0;
};

template<typename PacketType>
class PacketExecutorImpl : public PacketExecutor {
    bool executePacket(Server *server, Client *cl, Packet *packet) final {
        return this->execute(server, cl, static_cast<PacketType*>(packet));
    }

    virtual bool execute(Server *server, Client *cl, PacketType *packet) = 0;
};

#endif /* !PACKETEXECUTOR_HPP_ */
