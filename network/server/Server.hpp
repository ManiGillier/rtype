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

    /* TMP */
    #include <network/packets/impl/NewPlayerPacket.hpp>
    #include <network/packets/impl/NewEnemyPacket.hpp>
    #include <network/packets/impl/NewBulletPacket.hpp>
    #include <network/packets/impl/DespawnPlayerPacket.hpp>
    #include <network/packets/impl/DespawnBulletPacket.hpp>
    #include <network/packets/impl/EnemyDiedPacket.hpp>
    #include <network/packets/impl/PlayerIdPacket.hpp>
    #include <network/packets/impl/GameOverPacket.hpp>
    #include <network/packets/impl/CAuthentificationPacket.hpp>
    #include <network/packets/impl/AuthentifiedPacket.hpp>

class Client;

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

        static std::vector<std::tuple<sockaddr_in, std::shared_ptr<Packet>>> &getUDPPacketsToSend()
        {
            static std::vector<std::tuple<sockaddr_in, std::shared_ptr<Packet>>> packets;
            return packets;
        }

        static void addUDPPacketToSend(sockaddr_in address, std::shared_ptr<Packet> p) {
            getUDPPacketsToSend().push_back(std::make_tuple(address, p));
        }

    private:
        [[maybe_unused]] Server &server;
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
        virtual ~Server() = default;
    private:
        void executePackets();
        void sendUDPPackets();
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

class AuthenticationExecutor : public
    PacketExecutorImplServer<CAuthentificationPacket, IPollable> {

    bool executeUnlogged(Server &server, sockaddr_in address,
        std::shared_ptr<CAuthentificationPacket> packet) {
        for (std::shared_ptr<IPollable> &c : server.getPollManager().getPool()) {
            if (c->getUUID() == packet->getUUID() && c->getClientAddress() == std::nullopt) {
                c->setClientAddress(address);
                c->sendPacket(create_packet(AuthentifiedPacket));
            }
        }
        return true;
    }

    int getPacketId() const {
        return PacketId::C_AUTHENTICATION_PACKET;
    }
};

#endif /* !SERVER_HPP_ */
