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
#include <memory>
#include <network/packets/Packet.hpp>
#include <queue>
#include <vector>

class NetworkManager
{
  public:
    NetworkManager(std::mutex &playersMutex,
                   std::vector<std::shared_ptr<Player>> &players);
    ~NetworkManager() = default;
    void queuePacket(std::shared_ptr<Packet> packet, std::size_t playerId = 0,
                     bool filter = false);
    void playerDied(std::size_t id);
    void flush();
    void clear();
    void clearId(std::size_t id);

  private:
    std::mutex &_playersMutex;
    std::vector<std::shared_ptr<Player>> &_players;
    std::queue<std::shared_ptr<Packet>> _packets;
    PacketFilter _filter;
};
#endif
