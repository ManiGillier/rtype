/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** network manager
*/

#include "NetworkManager.hpp"

NetworkManager::NetworkManager(std::string ip, int port)
{
    this->client = std::make_unique<Client>(ip, port);
    this->networkThread = std::thread(&NetworkManager::loop, this);
}

NetworkManager::~NetworkManager()
{
    this->stop();
    if (this->networkThread.joinable())
        this->networkThread.join();
}

auto NetworkManager::loop() -> void
{
    this->client->connect();
    if (!this->client->isConnected())
        return;
    while (!this->shouldStop && this->client->isConnected()) {
        this->client->loop();
        if (!this->client->isConnected())
            break;
    }
}

auto NetworkManager::stop() -> void
{
    this->shouldStop = true;
}

auto NetworkManager::addExecutor(std::unique_ptr<PacketExecutor<Client>> exec)
 -> void
{
    this->client->getPacketListener().addExecutor(std::move(exec));
}

auto NetworkManager::getClient() -> Client &
{
    return *this->client;
}

auto NetworkManager::resetExecutors() -> void
{
    // TODO: fix this
    // this->client->getPacketListener().clearExecutors();
}

auto NetworkManager::sendPacket(std::shared_ptr<Packet> p) -> void
{
    this->client->sendPacket(p);
}
