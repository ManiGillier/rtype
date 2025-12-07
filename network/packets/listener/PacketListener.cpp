/*
** EPITECH PROJECT, 2025
** rtype [WSL: Ubuntu-24.04]
** File description:
** PacketListener
*/

#include "PacketListener.hpp"

PacketListener::PacketListener()
{
}

PacketListener::~PacketListener()
{
}

bool PacketListener::addExecutor(std::unique_ptr<PacketExecutor> &executor)
{
    this->executors.push_back(std::move(executor));
    return true;
}

bool PacketListener::removeExecutor(std::unique_ptr<PacketExecutor> &executor)
{
    for (size_t i = 0; i < this->executors.size(); i++) {
        if (this->executors[i] == executor) {
            this->executors.erase(this->executors.begin() + i);
            return true;
        }
    }
    return false;
}

bool PacketListener::removeExecutor(int packetId)
{
    for (size_t i = 0; i < this->executors.size(); i++) {
        if (this->executors[i]->getPacketId() == packetId) {
            this->executors.erase(this->executors.begin() + i);
            return true;
        }
    }
    return false;
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
