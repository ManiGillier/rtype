/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** Client
*/

#include <network/client/Client.hpp>
#include <network/logger/Logger.hpp>
#include <network/packets/PacketLogger.hpp>
#include <network/packets/PacketManager.hpp>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include <netdb.h>
#include "Client.hpp"

#include <network/packets/impl/CAuthentificationPacket.hpp>

Client::Client(const std::string &ip, int port)
{
    this->ip = ip;
    this->port = port;
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    int optVal = 1;

    this->fd = serverSocket;
    if (serverSocket != -1)
        setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR,
               &optVal, sizeof(optVal));
    this->getPacketListener().addPersistentExecutor(std::make_unique<ClientAuthExecutor>());
    this->getPacketListener().addPersistentExecutor(std::make_unique<ClientSetAuthExecutor>());
}

bool Client::connect()
{
    struct addrinfo hints, *res;
    struct sockaddr_in params;

    if (this->connected)
        return false;
    LOG("Trying to connect to " << ip << ":" << port << "..");
    if (this->fd == -1)
        return false;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    std::string port_str = std::to_string(this->port);
    if (getaddrinfo(this->ip.c_str(), port_str.c_str(), &hints, &res) != 0)
        return false;
    memcpy(&params, res->ai_addr, sizeof(sockaddr_in));
    freeaddrinfo(res);
    if (::connect(this->fd, reinterpret_cast<sockaddr*>(&params), sizeof(sockaddr_in)) == -1)
        return false;
    this->udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (this->udpSocket == -1)
        return false;
    if (::connect(this->udpSocket, reinterpret_cast<sockaddr*>(&params), sizeof(sockaddr_in)) == -1) {
        close(this->udpSocket);
        this->udpSocket = -1;
        return false;
    }
    this->connected = true;
    this->pm.addPollable(std::make_shared<ClientPollableUDP>(*this, this->udpSocket, params));
    this->pm.addPollable(std::make_shared<ClientPollable>(*this, this->fd));
    this->udpServerAddress = params;
    return this->connected;
}

bool Client::disconnect()
{
    LOG("Trying to disconnect from " << this->ip << ":" << this->port << "..");

    if (!this->connected)
        return false;
    if (this->fd != -1)
        close(this->fd);
    this->fd = -1;
    if (this->udpSocket != -1)
        close(udpSocket);
    this->udpSocket = -1;
    this->connected = false;
    this->pm.clear();
    this->authentified = false;
    this->getPacketListener().clearExecutors();
    return true;
}
bool Client::isConnected() const
{
    return this->connected;
}

bool Client::sendPacket(std::shared_ptr<Packet> p, bool wakeUpPoll)
{
    if (!this->connected || this->getPollManager().getConnectionCount() == 0)
        return false;
    for (std::shared_ptr<IPollable> &pollable : this->getPollManager().getPool())
        pollable->sendPacket(p, wakeUpPoll);
    return true;
}

void Client::executePackets()
{
    this->getPollManager().lock();
    for (std::shared_ptr<IPollable> &p : this->getPollManager().getPool()) {
        std::queue<std::shared_ptr<Packet>> &q = p->getReceivedPackets();
        while (!q.empty()) {
            std::shared_ptr<Packet> packet = q.front();
            this->getPacketListener().executePacket(*this, p, packet);
            q.pop();
        }
    }
    for (auto &[addr, packet] : ClientPollableUDP::getUDPReceivedPackets()) {
        this->getPacketListener().executePacket(*this,
            this->getPollManager().getPollableByAddress(this->udpServerAddress),
            packet);
    }
    ClientPollableUDP::getUDPReceivedPackets().clear();
    this->getPollManager().unlock();
}

void Client::sendUDPPackets()
{
    std::lock_guard<std::mutex> lck (this->udpLockSend);

    for (std::shared_ptr<IPollable> &p : this->getPollManager().getPool()) {
        for (auto &[packet, addr] : p->getPacketsToSendUDP()) {
            (void) addr;
            packet->clearData();
            packet->serialize();
            std::vector<uint8_t> toSend;
            toSend.push_back(packet->getId());
            std::queue<uint8_t> packetData = packet->getData();
            while (!packetData.empty()) {
                toSend.push_back(packetData.front());
                packetData.pop();
            }
            sendto(this->udpSocket, toSend.data(), toSend.size(), 0,
                (struct sockaddr*)&(this->udpServerAddress), sizeof(this->udpServerAddress));
            PacketLogger::logPacket(packet, PacketLogger::PacketMethod::SENT, this->udpSocket);
        }
        p->getPacketsToSendUDP().clear();
    }
}

void Client::loop()
{
    if (!this->connected)
        return;
    if ((this->connected && this->getPollManager().getConnectionCount() == 1) ||
        (this->connected && this->authentified &&
        this->getPollManager().getConnectionCount() == 2)) {
        this->connected = false;
        if (this->fd != -1) {
            close(this->fd);
            this->fd = -1;
        }
        if (this->udpSocket != -1) {
            close(this->udpSocket);
            this->udpSocket = -1;
        }
    }
    if (!this->authentified && this->retries <= MAX_RETRIES) {
        this->sendUDPPackets();
        this->getPollManager().pollSockets(1000);
        this->retries++;
        if (this->uuid != 0)
            this->sendPacket(std::make_unique<CAuthentificationPacket>(this->uuid));
        return;
    }
    this->sendUDPPackets();
    this->getPollManager().pollSockets();
}

const std::string &Client::getIp() const
{
    return this->ip;
}

int Client::getPort() const
{
    return this->port;
}

PollManager &Client::getPollManager()
{
    return this->pm;
}

PacketListener<Client> &Client::getPacketListener()
{
    return this->pl;
}

void Client::setUUID(uint32_t uuid)
{
    this->uuid = uuid;
}

void Client::setAuthentified(bool auth)
{
    this->authentified = auth;
}

bool Client::isAuthentified() const
{
    return this->authentified;
}

uint32_t Client::getUUID() const
{
    return this->uuid;
}

ClientPollable::ClientPollable(Client &cl, int fd) : Pollable(fd, cl.getPollManager()), cl(cl)
{
    return;
}

short ClientPollable::getFlags() const
{
    short flags = POLLIN;

    if (this->shouldWrite())
        flags |= POLLOUT;
    return flags;
}

bool ClientPollable::receiveEvent(short revent)
{
    if ((revent & POLLIN) != 0) {
        if (!this->getPacketReader().readPacket())
            return false;
        std::queue<std::shared_ptr<Packet>> &upcomingPackets =
            this->getPacketReader().getReceivedPackets();
        while (!upcomingPackets.empty()) {
            toProcess.push(upcomingPackets.front());
            upcomingPackets.pop();
        }
    }
    if (shouldWrite() && (revent & POLLOUT) != 0) {
        this->getPacketSender().writePackets();
        return true;
    }
    return true;
}

bool ClientPollable::shouldWrite() const
{
    return !this->getPacketSender().getPackets().empty();
}

ClientPollableUDP::ClientPollableUDP(Client &cl, int fd,
    sockaddr_in address) : ClientPollable(cl, fd), cl(cl)
{
    this->address = address;
    this->setClientAddress(address);
}


short ClientPollableUDP::getFlags() const
{
    return POLLIN;
}

bool ClientPollableUDP::receiveEvent(short)
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
