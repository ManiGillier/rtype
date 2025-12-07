/*
** EPITECH PROJECT, 2025
** rtype [WSL: Ubuntu-24.04]
** File description:
** PacketListener
*/

#ifndef PACKETLISTENER_HPP_
    #define PACKETLISTENER_HPP_

    #include "PacketExecutor.hpp"
    #include <vector>

class PacketListener {
    public:
        bool addExecutor(std::unique_ptr<PacketExecutor> &executor);
        bool removeExecutor(std::unique_ptr<PacketExecutor> &executor);
        bool removeExecutor(int packetId);
        bool clearExecutors();
        const std::vector<std::unique_ptr<PacketExecutor>> &getExecutors() const;
    private:
        std::vector<std::unique_ptr<PacketExecutor>> executors;
};

#endif /* !PACKETLISTENER_HPP_ */
