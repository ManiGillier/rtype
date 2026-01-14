#include "PacketFilter.hpp"

bool PacketFilter::shouldSend(std::size_t id, std::shared_ptr<Packet> newPacket)
{
    if (!newPacket)
        return false;

    auto it = _lastPackets.find(id);

    if (it == _lastPackets.end()) {
        _lastPackets[id][newPacket->getName()] = newPacket;
        return true;
    }
    auto packetIt = it->second.find(newPacket->getName());

    if (packetIt == it->second.end() ||
        !packetIt->second->isEqual(*newPacket)) {
        _lastPackets[id][newPacket->getName()] = newPacket;
        return true;
    }
    return false;
}

void PacketFilter::reset(std::size_t id)
{
    _lastPackets.erase(id);
}

void PacketFilter::resetAll()
{
    this->_lastPackets.clear();
}
