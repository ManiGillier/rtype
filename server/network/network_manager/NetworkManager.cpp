#include "NetworkManager.hpp"
#include <mutex>

NetworkManager::NetworkManager(std::mutex &playersMutex,
                               std::vector<std::shared_ptr<Player>> &players)
    : _playersMutex(playersMutex), _players(players)
{
}

void NetworkManager::queuePacket(std::shared_ptr<Packet> packet,
                                 std::size_t playerId, bool filter)

{
    if (!packet)
        return;
    if (!filter || (filter && _filter.shouldSend(playerId, packet)))
        _packets.push(packet);
}

void NetworkManager::playerDied(std::size_t id)
{
    std::lock_guard<std::mutex> lock(_playersMutex);
    for (auto it : _players) {
        if (it->getEntityId().has_value() && it->getEntityId().value() == id)
            it->setEntityId(std::nullopt);
    }
}

void NetworkManager::flush()
{
    while (!_packets.empty()) {
        auto p = _packets.front();
        {
            std::lock_guard<std::mutex> lock(this->_playersMutex);
            for (auto &it : _players) {
                it->sendPacket(p);
            }
        }
        _packets.pop();
    }
}

void NetworkManager::clear()
{
    while (!_packets.empty())
        _packets.pop();
    this->_filter.resetAll();
}

void NetworkManager::clearId(std::size_t id)
{
    this->_filter.reset(id);
}

void NetworkManager::setLastTick(float last)
{
    this->_lastTick = last;
}

float NetworkManager::getLastTick() const
{
    return this->_lastTick;
}
