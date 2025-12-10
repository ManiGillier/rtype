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

class ServerClient : public Pollable {
    public:
        ServerClient(int fd, PollManager &pm);
        short getFlags() const;
        bool receiveEvent(short revent);
        void sendPacket(std::shared_ptr<Packet> &p);
        std::queue<std::shared_ptr<Packet>> &getReceivedPackets();
    private:
        bool shouldWrite() const;
        PollManager &pm;
        /* TODO: Is this the way..? */
        std::queue<std::shared_ptr<Packet>> toProcess;
};

#endif /* !CONNECTION_HPP_ */
