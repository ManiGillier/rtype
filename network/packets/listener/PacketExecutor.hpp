/*
** EPITECH PROJECT, 2025
** rtype [WSL: Ubuntu-24.04]
** File description:
** PacketExecutor
*/

#ifndef PACKETEXECUTOR_HPP_
    #define PACKETEXECUTOR_HPP_

class Server;
class Client;

    #include <network/packets/Packet.hpp>
    #include <network/poll/IPollable.hpp>

template<typename EndType>
class PacketExecutor {
    public:
        // Server and clients are both null if its a Client Executor
        virtual bool executePacket(EndType &server,
            std::shared_ptr<IPollable> con, std::shared_ptr<Packet> packet) = 0;
        virtual bool executePacketUnlogged(EndType &server,
            sockaddr_in address, std::shared_ptr<Packet> packet) = 0;
        virtual ~PacketExecutor() = default;
        virtual int getPacketId() const = 0;
};

template<typename PacketType, typename ClientType, typename EndType>
class PacketExecutorImpl : public PacketExecutor<EndType> {
    bool executePacket(EndType &server, std::shared_ptr<IPollable> con,
            std::shared_ptr<Packet> packet) final {
        std::shared_ptr<PacketType> typedPacket = std::static_pointer_cast<PacketType>(packet);
        std::shared_ptr<ClientType> typedClient = std::static_pointer_cast<ClientType>(con);

        return this->execute(server, typedClient, typedPacket);
    }
    
    bool executePacketUnlogged(EndType &server, sockaddr_in address,
        std::shared_ptr<Packet> packet) final {
        std::shared_ptr<PacketType> typedPacket = std::static_pointer_cast<PacketType>(packet);
    
        return this->executeUnlogged(server, address, typedPacket);
    }

    virtual bool executeUnlogged(EndType &server, sockaddr_in address,
        std::shared_ptr<PacketType> packet) {
        (void) server;
        (void) address;
        (void) packet;
        return false;
    }

    virtual bool execute(EndType &server, std::shared_ptr<ClientType> con,
        std::shared_ptr<PacketType> packet) {
        (void) server;
        (void) con;
        (void) packet;
        return true;
    }
};

template<typename PacketType, typename ClientType>
class PacketExecutorImplServer :
    public PacketExecutorImpl<PacketType, ClientType, Server> {};

template<typename PacketType, typename ClientType>
class PacketExecutorImplClient :
    public PacketExecutorImpl<PacketType, ClientType, Client> {};

#endif /* !PACKETEXECUTOR_HPP_ */
