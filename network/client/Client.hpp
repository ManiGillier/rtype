/*
** EPITECH PROJECT, 2025
** rtype [WSL: Ubuntu-24.04]
** File description:
** Client
*/

#ifndef CLIENT_HPP_
    #define CLIENT_HPP_

    #include <network/packets/PacketReader.hpp>
    #include <network/packets/PacketSender.hpp>
    #include <network/packets/listener/PacketListener.hpp>
    #include <network/poll/PollManager.hpp>
    #include <network/poll/Pollable.hpp>
    #include <string>

class ClientPollable;

class Client {
    public:
        Client(const std::string &ip, int port);
        bool connect();
        bool disconnect();
        bool isConnected() const;
        bool sendPacket(std::shared_ptr<Packet> p);
        void executePackets();
        void loop();
        const std::string &getIp() const;
        int getPort() const;
        PollManager &getPollManager();
        PacketListener<Client> &getPacketListener();
    private:
        std::string ip;
        int port;
        int fd = -1;
        PollManager pm;
        PacketListener<Client> pl;
        bool connected = false;
};

class ClientPollable : public Pollable {
    public:
        ClientPollable(Client &cl, int fd);
        short getFlags() const;
        bool receiveEvent(short revent);
    private:
        bool shouldWrite() const;
        [[maybe_unused]] Client &cl;
};

#endif /* !CLIENT_HPP_ */
