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
    #include <vector>

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
            std::cout << "Custom : " << port << std::endl;
        };

        std::shared_ptr<IPollable> createClient(int fd) {
            return std::make_shared<ServerClient>(fd, this->getPollManager());
        }

        void onClientConnect(std::shared_ptr<IPollable> client) {
            LOG("Client" << client->getFileDescriptor() << " connected !");
        }

        void onClientDisconnect(std::shared_ptr<IPollable> client) {
            LOG("Client" << client->getFileDescriptor() << " disconnected !");
        }
};

#endif /* !SERVER_HPP_ */
