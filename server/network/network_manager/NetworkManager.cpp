#include "NetworkManager.hpp"
#include "network/packets/Packet.hpp"
#include "network/packets/impl/DestroyEntityPacket.hpp"
#include "network/packets/impl/PositionUpdatePacket.hpp"
#include <mutex>

NetworkManager::NetworkManager(std::mutex &playersMutex,
                               std::vector<std::shared_ptr<Player>> &players)
    : _playersMutex(playersMutex), _players(players)
{
}

void NetworkManager::queuePacket(std::shared_ptr<Packet> packet)

{
    if (!packet)
        return;
    _packets.push(packet);
}

void NetworkManager::queuePosUpdate(PositionData pos)
{
    _posData.push_back(pos);
}

void NetworkManager::queueDiedEntity(uint16_t toKill)
{
    _toDestroy.push_back(toKill);
}

void NetworkManager::playerDied(std::size_t id)
{
    std::lock_guard<std::mutex> lock(_playersMutex);
    for (auto &it : _players) {
        if (it->getEntityId().has_value() &&
            it->getEntityId().value().first == id)
            it->setEntityId(std::nullopt);
    }
}

void NetworkManager::sendEntityUpdate()
{
    auto entityPosPacket =
        !this->_posData.empty()
            ? create_packet(PositionUpdatePacket, this->_posData)
            : nullptr;
    auto entityToDestroyPacket =
        !this->_toDestroy.empty()
            ? create_packet(DestroyEntityPacket, this->_toDestroy)
            : nullptr;

    if (entityPosPacket)
        this->queuePacket(entityPosPacket);
    if (entityToDestroyPacket)
        this->queuePacket(entityToDestroyPacket);
}

void NetworkManager::clearEntityUpdate()
{
    this->_posData.clear();
    this->_toDestroy.clear();
}

void NetworkManager::flush()
{
    this->sendEntityUpdate();
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
    this->clearEntityUpdate();
}

void NetworkManager::clear()
{
    while (!_packets.empty())
        _packets.pop();
}

void NetworkManager::setLastTick(float last)
{
    this->_lastTick = last;
}

float NetworkManager::getLastTick() const
{
    return this->_lastTick;
}

void NetworkManager::playerScoreUpsate(std::size_t id, int score)
{
    std::lock_guard<std::mutex> lock(_playersMutex);
    for (auto &it : _players) {
        if (it->getEntityId().has_value() &&
            it->getEntityId().value().first == id)
            it->addScore(score);
    }
}

void NetworkManager::savePlayersScore()
{
    std::lock_guard<std::mutex> lock(_playersMutex);
    for (auto &it : _players) {
            // it->saveScore();
    }
}
