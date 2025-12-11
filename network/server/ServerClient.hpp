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
    private:
        bool shouldWrite() const;
        [[maybe_unused]] PollManager &pm;
};

#endif /* !CONNECTION_HPP_ */
