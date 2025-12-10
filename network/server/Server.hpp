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
    #include <network/packets/impl/ScoreUpdatePacket.hpp>

class Client;

class ServerPollable : public Pollable {
    public:
        ServerPollable(Server &server, int fd);
        short getFlags() const;
        bool receiveEvent(short revent);
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
        PacketListener &getPacketListener();
        PollManager &getPollManager();
        virtual std::shared_ptr<IPollable> createClient(int fd) = 0;
        virtual void onClientConnect(std::shared_ptr<IPollable> client) = 0;
        virtual void onClientDisconnect(std::shared_ptr<IPollable> client) = 0;
        virtual ~Server() = default;
    private:
        int port;
        int fd;
        bool upStatus = false;
        PacketListener pl;
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

            std::shared_ptr<ServerClient> sc = std::static_pointer_cast<ServerClient>(client);
            std::shared_ptr<Packet> p = create_packet(ScoreUpdatePacket, 69, 727, 420);
            sc->sendPacket(p);
        }

        void onClientDisconnect(std::shared_ptr<IPollable> client) {
            LOG("Client [" << client->getFileDescriptor() << "] disconnected !");
        }
};

#endif /* !SERVER_HPP_ */
