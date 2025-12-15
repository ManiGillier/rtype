/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** IPollable
*/

#ifndef IPOLLABLE_HPP_
    #define IPOLLABLE_HPP_

    #include <network/packets/Packet.hpp>
    #include <optional>

    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>

class IPollable {
    public:
        virtual ~IPollable() = default;
        virtual int getFileDescriptor() = 0;
        virtual short getFlags() const = 0;
        virtual bool receiveEvent(short revent) = 0;
        virtual uint32_t getUUID() const = 0;
        virtual std::optional<sockaddr_in> getClientAddress() const = 0;
        virtual void setClientAddress(std::optional<sockaddr_in> address) = 0;
        virtual void sendPacket(std::shared_ptr<Packet> p) = 0;
        virtual std::queue<std::shared_ptr<Packet>> &getReceivedPackets() = 0;
        virtual std::vector<std::tuple<std::shared_ptr<Packet>,
            std::optional<sockaddr_in>>> &getPacketsToSendUDP() = 0;
};

#endif /* !IPOLLABLE_HPP_ */
