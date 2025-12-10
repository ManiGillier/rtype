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
    #include <string>

class Client {
    public:
        Client(std::string ip, int port);
        bool connect();
        bool disconnect();
        bool isConnected() const;
        const std::string &getIp() const;
        const int getPort() const;
    private:
        std::string ip;
        int port;
        int fd = -1;
        bool connected = false;
};

#endif /* !CLIENT_HPP_ */
