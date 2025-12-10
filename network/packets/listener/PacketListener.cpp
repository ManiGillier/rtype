/*
** EPITECH PROJECT, 2025
** rtype [WSL: Ubuntu-24.04]
** File description:
** PacketListener
*/

#include "PacketListener.hpp"

bool PacketListener::addExecutor(std::unique_ptr<PacketExecutor> &executor)
{
    this->executors.push_back(std::move(executor));
    return true;
}

bool PacketListener::removeExecutor(std::unique_ptr<PacketExecutor> &executor)
{
    for (auto it = this->executors.begin(); it != this->executors.end(); it++) {
        if (*it == executor) {
            this->executors.erase(it);
            return true;
        }
    }
    return false;
}

bool PacketListener::removeExecutor(int packetId)
{
    for (auto it = this->executors.begin(); it != this->executors.end(); it++) {
        if ((*it)->getPacketId() == packetId) {
            this->executors.erase(it);
            return true;
        }
    }
    return false;
}

bool PacketListener::executePacket(Server &server, std::shared_ptr<IPollable> &con,
    std::shared_ptr<Packet> &p) const
{
    bool status = true;

    for (const std::unique_ptr<PacketExecutor> &packetExecutor : this->executors) {
        if (packetExecutor->getPacketId() == p->getId())
            status = packetExecutor->executePacket(server, con, p) && status;
    }
    return status;
}

bool PacketListener::clearExecutors()
{
    this->executors.clear();
    return true;
}

const std::vector<std::unique_ptr<PacketExecutor>> &PacketListener::getExecutors() const
{
    return this->executors;
}
