/*
** EPITECH PROJECT, 2025
** rtype [WSL: Ubuntu-24.04]
** File description:
** Server
*/

#ifndef SERVER_HPP_
    #define SERVER_HPP_

    #include "PacketListener.hpp"
    #include <vector>
class Client;

class Server {
    public:
        Server(int port);
        bool up();
        bool down();
        bool isUp() const;
        void loop();
        PacketListener &getPacketListener();
        std::vector<Client> &getClients();
    private:
        int port;
        bool upStatus = false;
        PacketListener pl;
        std::vector<Client> clients;
};

#endif /* !SERVER_HPP_ */
