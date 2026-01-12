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
#include <network/packets/PacketCompressor.hpp>
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
            try {
                packet->serialize();
            } catch (const Packet::PacketException &e) {
                LOG_ERR(e.what());
                continue;
            }
            std::vector<uint8_t> toSend;
            std::vector<uint8_t> compressed;
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
    if ((this->connected && !isAuthentified() &&this->getPollManager().getConnectionCount() == 2) ||
        (this->connected && this->authentified &&
        this->getPollManager().getConnectionCount() == 2) || (this->getPollManager().getConnectionCount() == 1)) {
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

void Client::updateSequenceNum(uint16_t receivedSequence)
{
    if (this->firstUDPPacket) {
        this->lastReceivedSeqNum = receivedSequence;
        this->firstUDPPacket = false;
    } else {
        int16_t diff = (int16_t) (receivedSequence - this->lastReceivedSeqNum);
        if (diff <= 0) {
            return;
        }
        if (diff > 1) {
            uint16_t packetsLost = static_cast<uint16_t>(diff - 1);
            this->totalPacketsLost += packetsLost;
        }

        this->lastReceivedSeqNum = receivedSequence;
    }
}

double Client::getPacketLossPercentage() const
{
    if (this->firstUDPPacket)
        return 0.0;
    uint32_t totalReceived = static_cast<uint32_t>(this->lastReceivedSeqNum) + 1;
    uint32_t totalExpected = totalReceived + this->totalPacketsLost;

    return (static_cast<double>(this->totalPacketsLost) /
        static_cast<double>(totalExpected)) * 100.0;
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
        std::lock_guard<std::mutex> lck (cl.tcpLockSend);
        this->getPacketSender().writePackets();
        return true;
    }
    return true;
}

bool ClientPollable::shouldWrite() const
{
    return this->getPacketSender().shouldSend();
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
    std::vector<uint8_t> receivedData;
    ssize_t bytesRead = recvfrom(this->getFileDescriptor(), buffer, BUFFER_SIZE, 0,
                                  (struct sockaddr*)&sender, &senderLen);
    if (bytesRead <= 0)
        return true;
    for (ssize_t i = 0; i < bytesRead; i++)
        receivedData.push_back(buffer[i]);
    while (!receivedData.empty()) {
        std::shared_ptr<Packet> packet = nullptr;
        uint8_t packetId = 0;
        uint16_t sequenceNum = 0;
        uint32_t originalSize = 0;
        uint32_t compressedSize = 0;
        try {
            Packet::fromBinary(receivedData, sequenceNum);
            packetId = receivedData[0];
            receivedData.erase(receivedData.begin());
            packet = PacketManager::getInstance().createPacketById(packetId, Packet::PacketMode::UDP);
            if (packet == nullptr) {
                LOG_ERR("Received invalid packet ID: " << (int) packetId);
                break;
            }
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
        } catch (const std::exception &e) {
            LOG_ERR("Could not read UDP packet with ID " << (int) packetId);
            receivedData.clear();
            break;
        }
        PacketLogger::logPacket(packet, PacketLogger::PacketMethod::RECEIVED,
            this->getFileDescriptor(), sequenceNum);
        addReceivedPacket(sender, packet);
        receivedData.erase(receivedData.begin(), 
            std::next(receivedData.begin(), static_cast<std::ptrdiff_t>(compressedSize)));
        cl.updateSequenceNum(sequenceNum);
    }
    return true;
}
