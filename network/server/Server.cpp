/*
** EPITECH PROJECT, 2025
** rtype [WSL: Ubuntu-24.04]
** File description:
** Server
*/

#include <network/packets/impl/SAuthentificationPacket.hpp>

#include <network/logger/Logger.hpp>
#include <network/server/Server.hpp>
#include <network/server/ServerClient.hpp>
#include <network/server/Server.hpp>
#include <network/packets/PacketLogger.hpp>
#include <string>

#include <poll.h>
#include <unistd.h>
#include <poll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <bits/stdc++.h>
#include "Server.hpp"

Server::Server(int port)
{
    this->port = port;
    this->getPacketListener().addExecutor(std::make_unique<AuthenticationExecutor>());
}

/* TODO: Refactor this method, HOLY TRUMP WALL */
bool Server::up()
{
    LOG("Starting server at " << this->port << "..");

    if (this->upStatus)
        return false;
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    int optVal = 1;
    struct sockaddr_in params;

    memset(&params, 0, sizeof(sockaddr));
    params.sin_family = AF_INET;
    params.sin_addr.s_addr = INADDR_ANY;
    params.sin_port = htons((uint16_t) port);
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &optVal, sizeof(optVal));
    if (bind(serverSocket, (struct sockaddr *) &params, sizeof(struct sockaddr_in)) == -1)
        return this->upStatus;
    if (listen(serverSocket, SOMAXCONN) == -1)
        return this->upStatus;
    int udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
    setsockopt(udpSocket, SOL_SOCKET, SO_REUSEADDR, &optVal, sizeof(optVal));
    if (bind(udpSocket, (struct sockaddr *) &params, sizeof(struct sockaddr_in)) == -1) {
        close(serverSocket);
        return this->upStatus;
    }
    this->upStatus = true;
    this->fd = serverSocket;
    this->udpFd = udpSocket;
    this->getPollManager().addPollable(
        std::make_shared<ServerPollable>(*this, fd));
    this->getPollManager().addPollable(
        std::make_shared<ServerUDPPollable>(*this, udpFd));
    LOG("Could start server at " << this->port << " !");
    return this->upStatus;
}

/* TODO: down UDP server as well */
bool Server::down()
{
    LOG("Stopping server at " << this->port << "..");
    if (this->upStatus) {
        shutdown(this->fd, SHUT_RDWR);
        this->pm.clear();
        this->upStatus = false;
        LOG("Could stop server at " << this->port << " !");
        return !this->upStatus;
    }
    LOG_ERR("Could not stop server: Server was not up.");
    return !this->upStatus;
}

bool Server::isUp() const
{
    return this->upStatus;
}

void Server::loop()
{
    if (!this->upStatus)
        return;
    this->sendUDPPackets();
    for (std::shared_ptr<IPollable> pd : this->getPollManager().pollSockets())
        this->onClientDisconnect(pd);
    this->executePackets();
}

PacketListener<Server> &Server::getPacketListener()
{
    return this->pl;
}

PollManager &Server::getPollManager()
{
    return this->pm;
}

/* TODO: Implement logged execute on UDP */
void Server::executePackets()
{
    std::vector<int> toRemove;

    this->getPollManager().lock();
    for (std::shared_ptr<IPollable> &p : this->getPollManager().getPool()) {
        std::queue<std::shared_ptr<Packet>> &q = p->getReceivedPackets();
        while (!q.empty()) {
            std::shared_ptr<Packet> packet = q.front();
            if (!this->getPacketListener().executePacket(*this, p, packet))
                toRemove.push_back(p->getFileDescriptor());
            q.pop();
        }
    }
    for (auto &[sender, packet] : ServerUDPPollable::getUDPReceivedPackets()) {
        std::shared_ptr<IPollable> client = this->getPollManager().getPollableByAddress(sender);

        if (!client)
            this->getPacketListener().executePacket(*this, sender, packet);
        else if (!this->getPacketListener().executePacket(*this, client, packet))
            toRemove.push_back(client->getFileDescriptor());
    }
    ServerUDPPollable::getUDPReceivedPackets().clear();
    for (int fdClient : toRemove)
        this->getPollManager().removePollable(fdClient);
    this->getPollManager().unlock();
}

void Server::sendUDPPackets()
{
    std::lock_guard<std::mutex> lck (this->udpLock);
    std::vector<std::shared_ptr<IPollable>> pool = this->getPollManager().getPool();

    for (std::shared_ptr<IPollable> &p : pool) {
        for (auto &[packet, addr] : p->getPacketsToSendUDP()) {
            if (addr == std::nullopt)
                continue;
            packet->clearData();
            packet->serialize();
            std::vector<uint8_t> toSend;
            toSend.push_back(packet->getId());
            std::queue<uint8_t> packetData = packet->getData();
            while (!packetData.empty()) {
                toSend.push_back(packetData.front());
                packetData.pop();
            }
            sendto(this->udpFd, toSend.data(), toSend.size(), 0,
                (struct sockaddr*)&(addr.value()), sizeof(addr.value()));
            PacketLogger::logPacket(packet, PacketLogger::PacketMethod::SENT, this->udpFd);
        }
        p->getPacketsToSendUDP().clear();
    }
}

ServerPollable::ServerPollable(Server &server, int fd)
    : Pollable(fd, server.getPollManager()), server(server)
{
    return;
}

short ServerPollable::getFlags() const
{
    return POLLIN;
}

bool ServerPollable::receiveEvent(short revent)
{
    int other_socket = accept(this->getFileDescriptor(), 0, 0);
    std::shared_ptr<IPollable> createdClient = nullptr;

    (void) revent;
    if (other_socket < 0)
        return true;
    createdClient = server.createClient(other_socket);
    this->server.getPollManager().addPollable(createdClient);
    this->server.onClientConnect(createdClient);
    createdClient->sendPacket(create_packet(SAuthentificationPacket, createdClient->getUUID()));
    return true;
}

ServerUDPPollable::ServerUDPPollable(Server &server, int fd) :
    Pollable(fd, server.getPollManager()), server(server)
{
    return;
}

short ServerUDPPollable::getFlags() const
{
    return POLLIN;
}

bool ServerUDPPollable::receiveEvent(short)
{
    uint8_t buffer[BUFFER_SIZE];
    struct sockaddr_in sender;
    socklen_t senderLen = sizeof(sender);
    std::queue<uint8_t> dataQueue;
    ssize_t bytesRead = recvfrom(this->getFileDescriptor(), buffer, BUFFER_SIZE, 0,
                                  (struct sockaddr*)&sender, &senderLen);
    if (bytesRead <= 0)
        return true;
    for (ssize_t i = 0; i < bytesRead; i++)
        dataQueue.push(buffer[i]);
    while (!dataQueue.empty()) {
        uint8_t packetId = dataQueue.front();
        dataQueue.pop();
        std::shared_ptr<Packet> packet = PacketManager::getInstance().createPacketById(packetId, Packet::PacketMode::UDP);
        if (packet == nullptr) {
            LOG_ERR("Received invalid packet ID: " << (int) packetId);
            break;
        }
        std::size_t packetSize = (std::size_t)packet->getSize();
        if (packetSize > dataQueue.size()) {
            LOG_ERR("Incomplete packet received with ID (" << (int) packetId << ")");
            break;
        }
        std::queue<uint8_t> packetData;
        for (std::size_t i = 0; i < packetSize; i++) {
            packetData.push(dataQueue.front());
            dataQueue.pop();
        }
        packet->setData(packetData);
        packet->unserialize();
        PacketLogger::logPacket(packet, PacketLogger::PacketMethod::RECEIVED,
            this->getFileDescriptor());
        addReceivedPacket(sender, packet);
    }
    return true;
}

