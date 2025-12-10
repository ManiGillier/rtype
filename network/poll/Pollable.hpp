/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** Pollable
*/

#ifndef POLLABLE_HPP_
    #define POLLABLE_HPP_

    #include <network/poll/IPollable.hpp>
    #include <network/packets/PacketReader.hpp>
    #include <network/packets/PacketSender.hpp>
    #include <network/poll/PollManager.hpp>

class Pollable : public IPollable {
    public:
        Pollable(int fd) : _fd(fd), sender(fd), reader(fd) {};

        int getFileDescriptor() {
            return this->_fd;
        }

        PacketSender &getPacketSender() {
            return this->sender;
        }

        const PacketSender &getPacketSender() const {
            return this->sender;
        }

        PacketReader &getPacketReader() {
            return this->reader;
        }

        const PacketReader &getPacketReader() const {
            return this->reader;
        }

    private:
        int _fd;
        PacketSender sender;
        PacketReader reader;
};

#endif /* !POLLABLE_HPP_ */
