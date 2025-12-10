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

class Client {
    public:
        Client(const std::string &ip, int port);
        bool connect();
        bool disconnect();
        bool isConnected() const;
        void loop();
        const std::string &getIp() const;
        int getPort() const;
        PollManager &getPollManager();
    private:
        std::string ip;
        int port;
        int fd = -1;
        PollManager pm;
        bool connected = false;
};

class ClientPollable : public Pollable {
    public:
        ClientPollable(Client &cl, int fd);
        short getFlags() const;
        bool receiveEvent(short revent);
        void sendPacket(std::shared_ptr<Packet> &p);
        std::queue<std::shared_ptr<Packet>> &getReceivedPackets();
    private:
        bool shouldWrite() const;
        Client &cl;
        std::queue<std::shared_ptr<Packet>> toProcess;
        PacketListener pl;
};

#endif /* !CLIENT_HPP_ */
