/*
** EPITECH PROJECT, 2025
** rtype [WSL: Ubuntu-24.04]
** File description:
** Server
*/

#ifndef SERVER_HPP_
    #define SERVER_HPP_

    #include <vector>

class Client;

class Server {
    public:
        Server(int port);
        bool up() const;
        bool down() const;
        void loop();
        std::vector<Client> &getClients();
    private:
        int port;
        std::vector<Client> clients;
};

#endif /* !SERVER_HPP_ */
