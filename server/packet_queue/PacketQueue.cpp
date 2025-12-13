#include "PacketQueue.hpp"

void PacketQueue::clearReceived()
{
    std::lock_guard<std::mutex> lock(_receivedMutex);
    _receivedPackets.clear();
}

void PacketQueue::clearToSend()
{
    std::lock_guard<std::mutex> lock(_toSendMutex);
    _packetsToSend.clear();
}

void PacketQueue::addToSend(std::shared_ptr<Packet> packet)
{
    std::lock_guard<std::mutex> lock(_toSendMutex);
    _packetsToSend.push_back(packet);
}

void PacketQueue::addReceived(std::shared_ptr<Packet> packet)
{
    std::lock_guard<std::mutex> lock(_receivedMutex);
    _receivedPackets.push_back(packet);
}

std::vector<std::shared_ptr<Packet>> PacketQueue::getReceived()
{
    std::lock_guard<std::mutex> lock(_receivedMutex);
    return _receivedPackets;
}

std::vector<std::shared_ptr<Packet>> PacketQueue::getToSend()
{
    std::lock_guard<std::mutex> lock(_toSendMutex);
    return _packetsToSend;
}

std::vector<std::shared_ptr<Packet>> PacketQueue::popAllReceived()
{
    std::lock_guard<std::mutex> lock(_receivedMutex);
    std::vector<std::shared_ptr<Packet>> result = std::move(_receivedPackets);
    _receivedPackets.clear();
    return result;
}

std::vector<std::shared_ptr<Packet>> PacketQueue::popAllToSend()
{
    std::lock_guard<std::mutex> lock(_toSendMutex);
    std::vector<std::shared_ptr<Packet>> result = std::move(_packetsToSend);
    _packetsToSend.clear();
    return result;
}
