/*
** EPITECH PROJECT, 2025
** rtype [WSL: Ubuntu-24.04]
** File description:
** Client
*/

#ifndef CLIENT_HPP_
    #define CLIENT_HPP_

    #include "PacketReader.hpp"
    #include "PacketSender.hpp"


class Client : public IPollable {
    public:
        
    private:
        PacketReader packetReader;
        PacketSender packetSender;
};

#endif /* !CLIENT_HPP_ */
