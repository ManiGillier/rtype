/*
 ** EPITECH PROJECT, 2025
 ** rtype
 ** File description:
 ** network manager
 */

#ifndef NETWORK_MANAGER_HPP
#define NETWORK_MANAGER_HPP

#include "../../network/packet_filter/PacketFilter.hpp"
#include "../../player/Player.hpp"
#include <cstddef>
#include <cstdint>
#include <memory>
#include <network/packets/Packet.hpp>
#include <network/packets/impl/PositionUpdatePacket.hpp>
#include <queue>
#include <vector>

class NetworkManager
{
  public:
    NetworkManager(std::mutex &playersMutex,
                   std::vector<std::shared_ptr<Player>> &players);
    ~NetworkManager() = default;
    void queuePacket(std::shared_ptr<Packet> packet);
    void queuePosUpdate(PositionData pos);
    void queueDiedEntity(uint16_t toKill);
    void playerDied(std::size_t id);
    void sendToUniqueId(std::size_t id, std::shared_ptr<Packet> packet);
    void playerScoreUpsate(std::size_t id, int score);
    void savePlayersScore();
    void setLastTick(float last);
    float getLastTick() const;
    void flush();
    void clear();

  private:
    void sendEntityUpdate();
    void clearEntityUpdate();
    std::mutex &_playersMutex;
    std::vector<std::shared_ptr<Player>> &_players;
    std::queue<std::shared_ptr<Packet>> _packets;
    std::vector<PositionData> _posData;
    std::vector<uint16_t> _toDestroy;
    float _lastTick;
};
#endif
