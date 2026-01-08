#include "PacketFilter.hpp"

bool PacketFilter::shouldSend(std::size_t id, std::shared_ptr<Packet> newPacket)
{
    auto it = _lastPackets.find(id);

    if (it == _lastPackets.end() || !it->second->isEqual(*newPacket)) {
        _lastPackets[id] = newPacket;
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
