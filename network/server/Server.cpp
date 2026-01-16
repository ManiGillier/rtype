/*
** EPITECH PROJECT, 2025
** rtype [WSL: Ubuntu-24.04]
** File description:
** Server
*/

#include <network/packets/impl/SAuthentificationPacket.hpp>

#include <network/poll/WakeUpPollable.hpp>

#include <network/logger/Logger.hpp>
#include <network/packets/PacketLogger.hpp>
#include <network/packets/PacketCompressor.hpp>
#include <network/server/Server.hpp>
#include <network/server/ServerClient.hpp>
#include <string>

#include "Server.hpp"
#include <bits/stdc++.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <poll.h>
#include <sys/socket.h>
#include <unistd.h>

Server::Server(int port, int maxConnections)
{
    this->port = port;
    this->maxConnections = maxConnections;
    this->getPacketListener().addPersistentExecutor(
        std::make_unique<AuthenticationExecutor>());
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
    params.sin_port = htons((uint16_t)port);
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &optVal, sizeof(optVal));
    if (bind(serverSocket, (struct sockaddr *)&params,
             sizeof(struct sockaddr_in)) == -1)
        return this->upStatus;
    if (listen(serverSocket, SOMAXCONN) == -1)
        return this->upStatus;
    int udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
    setsockopt(udpSocket, SOL_SOCKET, SO_REUSEADDR, &optVal, sizeof(optVal));
    if (bind(udpSocket, (struct sockaddr *)&params,
             sizeof(struct sockaddr_in)) == -1) {
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
    this->maxConnections += (int)this->getPollManager().getPool().size();
    return this->upStatus;
}

/* TODO: down UDP server as well */
bool Server::down()
{
    LOG("Stopping server at " << this->port << "..");
    if (this->upStatus) {
        shutdown(this->fd, SHUT_RDWR);
        shutdown(this->udpFd, SHUT_RDWR);
        this->pm.clear();
        this->getPacketListener().clearExecutors();
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

int Server::getMaxConnections() const
{
    return this->maxConnections;
}

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
        std::shared_ptr<IPollable> client =
            this->getPollManager().getPollableByAddress(sender);

        if (!client)
            this->getPacketListener().executePacket(*this, sender, packet);
        else if (!this->getPacketListener().executePacket(*this, client,
                                                          packet))
            toRemove.push_back(client->getFileDescriptor());
    }
    ServerUDPPollable::getUDPReceivedPackets().clear();
    for (int fdClient : toRemove)
        this->getPollManager().removePollable(fdClient);
    this->getPollManager().unlock();
}

void Server::sendUDPPackets()
{
    std::lock_guard<std::mutex> lck(this->udpLock);
    std::vector<std::shared_ptr<IPollable>> pool =
        this->getPollManager().getPool();

    for (std::shared_ptr<IPollable> &p : pool) {
        for (auto &[packet, addr] : p->getPacketsToSendUDP()) {
            if (addr == std::nullopt)
                continue;
            packet->clearData();
            try {
                packet->serialize();
            } catch (const Packet::PacketException &e) {
                LOG_ERR(e.what());
                continue;
            }
            std::uint16_t &sequenceNum = p->getUDPPacketCount();

            std::vector<uint8_t> toSend;
            std::vector<uint8_t> compressed;
            std::vector<uint8_t> sequenceNumData = Packet::toBinary(sequenceNum);
            toSend.insert(toSend.end(), sequenceNumData.begin(), sequenceNumData.end());
            toSend.push_back(packet->getId());

            try {
                compressed = PacketCompressor::compress(packet->getData());
            } catch (const Packet::PacketException &e) {
                LOG_ERR(e.what());
                continue;
            }
            uint32_t oldPacketSize = (uint32_t) packet->getData().size();
            uint32_t newPacketSize =  (uint32_t) compressed.size();
            for (uint8_t bin : Packet::toBinary(oldPacketSize))
                toSend.push_back(bin);
            for (uint8_t bin : Packet::toBinary(newPacketSize))
                toSend.push_back(bin);
            toSend.insert(toSend.end(), compressed.begin(), compressed.end());

            sendto(this->udpFd, toSend.data(), toSend.size(), 0,
                   (struct sockaddr *)&(addr.value()), sizeof(addr.value()));
            sequenceNum += 1;
            PacketLogger::logPacket(packet, PacketLogger::PacketMethod::SENT,
                                    this->udpFd);
        }
        p->getPacketsToSendUDP().clear();
    }
}

bool Server::canConnect() const
{
    return this->enableConnection.load();
}

void Server::setConnect(bool c)
{
    this->enableConnection.store(c);
}

void Server::sendAll(std::shared_ptr<Packet> p)
{
    this->sendAll(this->getPollManager().getPool(), p);
}

void Server::disconnectClient(std::shared_ptr<IPollable> client)
{
    this->onClientDisconnect(this->getPollManager().
        removePollable(client->getFileDescriptor()));
}

void Server::sendAll(std::vector<std::shared_ptr<IPollable>> clients,
    std::shared_ptr<Packet> p)
{
    if (clients.empty())
        return;
    if (p->getMode() == Packet::PacketMode::TCP)
        std::lock_guard<std::mutex> lck(this->tcpLock);
    else
        std::lock_guard<std::mutex> lck(this->udpLock);
    for (std::shared_ptr<IPollable> cl : clients) {
        if (std::dynamic_pointer_cast<ServerUDPPollable>(cl) != nullptr ||
            std::dynamic_pointer_cast<ServerPollable>(cl) != nullptr ||
            std::dynamic_pointer_cast<WakeUpPollable>(cl) != nullptr)
            continue;
        std::shared_ptr<Pollable> pollable = std::dynamic_pointer_cast<Pollable>(cl);
        if (pollable == nullptr)
            continue;
        if (p->getMode() == Packet::PacketMode::TCP) {
            pollable->getPacketSender().sendPacket(p);
            this->getPollManager().updateFlags(cl->getFileDescriptor(), cl->getFlags());
        } else {
            pollable->getPacketsToSendUDP().emplace_back(p, cl->getClientAddress());
        }
        this->getPollManager().wakeUp();
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
    if ((this->server.getPollManager().getPool().size() >
         (std::size_t)this->server.getMaxConnections()) ||
        !this->server.canConnect()) {
        close(other_socket);
        return true;
    }
    std::shared_ptr<IPollable> createdClient = nullptr;

    (void)revent;
    if (other_socket < 0)
        return true;
    int flags = fcntl(other_socket, F_GETFL, 0);
    if (flags == -1 || fcntl(other_socket, F_SETFL, flags | O_NONBLOCK) == -1) {
        close(other_socket);
        return true;
    }
    createdClient = server.createClient(other_socket);
    this->server.getPollManager().addPollable(createdClient);
    this->server.onClientConnect(createdClient);
    createdClient->sendPacket(
        create_packet(SAuthentificationPacket, createdClient->getUUID()));
    return true;
}

ServerUDPPollable::ServerUDPPollable(Server &server, int fd)
    : Pollable(fd, server.getPollManager()), server(server)
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
    std::vector<uint8_t> receivedData;
    ssize_t bytesRead = recvfrom(this->getFileDescriptor(), buffer, BUFFER_SIZE,
                                 0, (struct sockaddr *)&sender, &senderLen);
    if (bytesRead <= 0)
        return true;
    for (ssize_t i = 0; i < bytesRead; i++)
        receivedData.push_back(buffer[i]);
    while (!receivedData.empty()) {
        uint8_t packetId = receivedData[0];
        uint32_t originalSize = 0;
        uint32_t compressedSize = 0;
        receivedData.erase(receivedData.begin());
        std::shared_ptr<Packet> packet =
            PacketManager::getInstance().createPacketById(
                packetId, Packet::PacketMode::UDP);
        if (packet == nullptr) {
            LOG_ERR("Received invalid packet ID: " << (int)packetId);
            break;
        }
        try {
            Packet::fromBinary(receivedData, originalSize);
            Packet::fromBinary(receivedData, compressedSize);
            if (receivedData.size() < compressedSize) {
                receivedData.clear();
                return true;
            }
            std::vector<uint8_t> packetData = PacketCompressor::decompress(receivedData,
                originalSize, compressedSize);
            packet->setData(packetData);
            packet->unserialize();
        } catch (const std::exception &) {
            LOG_ERR("Could not read UDP packet with ID " << (int) packetId);
            receivedData.clear();
            break;
        }
        PacketLogger::logPacket(packet, PacketLogger::PacketMethod::RECEIVED,
                                this->getFileDescriptor());
        addReceivedPacket(sender, packet);
        receivedData.erase(receivedData.begin(), 
            std::next(receivedData.begin(), static_cast<std::ptrdiff_t>(compressedSize)));
    }
    return true;
}
