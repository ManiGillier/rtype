/*
** EPITECH PROJECT, 2025
** rtype [WSL: Ubuntu-24.04]
** File description:
** Server
*/

#ifndef SERVER_HPP_
    #define SERVER_HPP_

    #include <network/packets/listener/PacketListener.hpp>
    #include <network/logger/Logger.hpp>
    #include <network/poll/PollManager.hpp>
    #include <network/server/ServerClient.hpp>
    #include <network/packets/PacketManager.hpp>
    #include <vector>

    #include <network/packets/impl/CAuthentificationPacket.hpp>

class Client;

class AuthenticationExecutor : public
    PacketExecutorImplServer<CAuthentificationPacket, IPollable> {

    /* TODO: Check if Client already exists with given UUID */
    bool executeUnlogged(Server &server, sockaddr_in address,
        std::shared_ptr<CAuthentificationPacket> packet) {

        (void) server;
        (void) packet;
        LOG(address.sin_addr.s_addr << " is trying to connect ! :O");

        return true;
    }

    int getPacketId() const {
        return PacketId::C_AUTHENTICATION_PACKET;
    }
};

class ServerPollable : public Pollable {
    public:
        ServerPollable(Server &server, int fd);
        short getFlags() const;
        bool receiveEvent(short revent);
    private:
        Server &server;
};

class ServerUDPPollable : public Pollable {
    public:
        ServerUDPPollable(Server &server, int fd);
        short getFlags() const;
        bool receiveEvent(short revent);

        /* TODO: Change this system for part 2 */

        static std::vector<std::tuple<sockaddr_in, std::shared_ptr<Packet>>> &getUDPReceivedPackets()
        {
            static std::vector<std::tuple<sockaddr_in, std::shared_ptr<Packet>>> packets;
            return packets;
        }

        static void addReceivedPacket(sockaddr_in address, std::shared_ptr<Packet> p) {
            getUDPReceivedPackets().push_back(std::make_tuple(address, p));
        }

    private:
        Server &server;
};

class Server {
    public:
        Server(int port);
        bool up();
        bool down();
        bool isUp() const;
        void loop();
        PacketListener<Server> &getPacketListener();
        PollManager &getPollManager();
        virtual std::shared_ptr<IPollable> createClient(int fd) = 0;
        virtual void onClientConnect(std::shared_ptr<IPollable> client) = 0;
        virtual void onClientDisconnect(std::shared_ptr<IPollable> client) = 0;
        void executePackets();
        virtual ~Server() = default;
    private:
        int port;
        int fd;
        int udpFd;
        bool upStatus = false;
        PacketListener<Server> pl;
        PollManager pm;
};

class CustomServer : public Server {
    public:
        CustomServer(int port) : Server(port) {
            return;
        }

        std::shared_ptr<IPollable> createClient(int fd) {
            return std::make_shared<ServerClient>(fd, this->getPollManager());
        }

        void onClientConnect(std::shared_ptr<IPollable> client) {
            LOG("Client [" << client->getFileDescriptor() << "] connected !");
        }

        void onClientDisconnect(std::shared_ptr<IPollable> client) {
            LOG("Client [" << client->getFileDescriptor() << "] disconnected !");
        }
};

#endif /* !SERVER_HPP_ */
