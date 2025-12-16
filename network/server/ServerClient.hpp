/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** Connection
*/

#ifndef CONNECTION_HPP_
    #define CONNECTION_HPP_

    #include <network/poll/PollManager.hpp>
    #include <network/poll/Pollable.hpp>

class Server;

class ServerClient : public Pollable {
    public:
        ServerClient(int fd, Server &s);
        short getFlags() const;
        bool receiveEvent(short revent);

        void sendPacket(std::shared_ptr<Packet> p, bool wakeUpPoll=true);
    private:
        bool shouldWrite() const;
        Server &serv;
};

#endif /* !CONNECTION_HPP_ */
