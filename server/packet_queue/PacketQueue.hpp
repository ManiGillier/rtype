#ifndef PACKETQUEUE_HPP
#define PACKETQUEUE_HPP

#include "../../network/packets/Packet.hpp"
#include <memory>
#include <mutex>
#include <queue>
#include <vector>

class PacketQueue
{
  public:
    PacketQueue() = default;
    ~PacketQueue() = default;

    void clearReceived();
    void clearToSend();
    void addToSend(std::shared_ptr<Packet> packet);
    void addReceived(std::shared_ptr<Packet> packet);
    std::vector<std::shared_ptr<Packet>> getReceived();
    std::vector<std::shared_ptr<Packet>> getToSend();
    std::vector<std::shared_ptr<Packet>> popAllReceived();
    std::vector<std::shared_ptr<Packet>> popAllToSend();

  private:
    std::vector<std::shared_ptr<Packet>> _receivedPackets;
    std::vector<std::shared_ptr<Packet>> _packetsToSend;
    mutable std::mutex _receivedMutex;
    mutable std::mutex _toSendMutex;
};

#endif
