/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** PlayerHit packet
*/

#ifndef PLAYERHIT_PACKET_HPP
#define PLAYERHIT_PACKET_HPP

#include "network/packets/Packet.hpp"
#include <cstddef>
#include <iostream>
#include <memory>

class PlayerHitPacket : public Packet
{
public:
    PlayerHitPacket(std::size_t id = 0, std::size_t hit_id = 0) :
        Packet(PacketId::PLAYER_HIT), id(id), hit_id(hit_id) {}

    enum PacketMode getMode() const {
        return PacketMode::TCP;
    }

    void serialize() {
        this->write(id);
        this->write(hit_id);
    }
    void unserialize() {
        this->read(id);
        this->read(hit_id);
    }

    const std::string getName() {
        return "PlayerHitPacket";
    }

    void display() {
        std::cout << "Id=" << this->id << ", HitId=" << this->hit_id;
    }
    auto getSize() const -> int { return sizeof(std::size_t) * 2; }

    std::shared_ptr<Packet> clone() const {
        return make_copy(PlayerHitPacket);
    }

    auto getEntityId() const -> std::size_t { return this->hit_id; }
    auto getPlayerId() const -> std::size_t { return this->id; }
private:
    std::size_t id;
    std::size_t hit_id;
};

#endif /* PLAYERHIT_PACKET_HPP */
