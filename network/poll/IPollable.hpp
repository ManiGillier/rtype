/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** IPollable
*/

#ifndef IPOLLABLE_HPP_
    #define IPOLLABLE_HPP_

    #include <network/packets/Packet.hpp>

class IPollable {
    public:
        virtual ~IPollable() = default;
        virtual int getFileDescriptor() = 0;
        virtual short getFlags() const = 0;
        virtual bool receiveEvent(short revent) = 0;
        virtual void sendPacket(std::shared_ptr<Packet> &p) = 0;
        virtual std::queue<std::shared_ptr<Packet>> &getReceivedPackets() = 0;
};

#endif /* !IPOLLABLE_HPP_ */
