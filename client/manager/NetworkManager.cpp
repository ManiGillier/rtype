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
    // TODO: Remove this temp fix
    Logger::shouldLog = true;
    this->client->connect();
    if (!this->client->isConnected())
        LOG_ERR("Failed to connect to server.");
    while (!this->shouldStop && this->client->isConnected()) {
        this->client->loop();
        if (!this->client->isConnected())
            break;
    }
    LOG("Connection ended.");
    this->shouldStop = true;
}

auto NetworkManager::stop() -> void
{
    this->shouldStop = true;
    this->client->getPollManager().wakeUp();
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
    this->client->getPacketListener().clearExecutors();
}

auto NetworkManager::sendPacket(std::shared_ptr<Packet> p) -> void
{
    this->client->sendPacket(p);
}
