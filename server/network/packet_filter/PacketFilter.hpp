/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** game
*/

#ifndef PACKET_FILTER_HPP
#define PACKET_FILTER_HPP

#include <unordered_map>
#include <memory>
#include <network/packets/Packet.hpp>

class PacketFilter
{
  public:
      PacketFilter() = default;
      ~PacketFilter() = default;
      bool shouldSend(std::size_t id, std::shared_ptr<Packet> newPacket);
      void reset(std::size_t id);
      void resetAll();
  private:
    std::unordered_map<std::size_t, std::shared_ptr<Packet>> _lastPackets;
};
 
#endif
