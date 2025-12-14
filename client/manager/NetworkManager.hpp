/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** network manager
*/

#ifndef CLIENT_NETWORK_MANAGER_HPP
#define CLIENT_NETWORK_MANAGER_HPP

#include <atomic>
#include <memory>
#include <network/client/Client.hpp>
#include <thread>

class NetworkManager
{
public:
    NetworkManager(std::string ip, int port);
    ~NetworkManager();

    auto loop() -> void;
    auto stop() -> void;

    auto addExecutor(std::unique_ptr<PacketExecutor<Client>>) -> void;
    auto resetExecutors() -> void;
    auto getClient() -> Client &;
private:
    std::atomic<bool> shouldStop = false;
    std::unique_ptr<Client> client;
    std::thread networkThread;
};

#endif /* CLIENT_NETWORK_MANAGER_HPP */
