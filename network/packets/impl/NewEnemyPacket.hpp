/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** NewEnemy packet
*/

#ifndef NEWENEMY_PACKET_HPP
#define NEWENEMY_PACKET_HPP

#include "network/packets/Packet.hpp"
#include <cstddef>
#include <memory>

enum class EnemyType { Enemy, Boss };

class NewEnemyPacket : public Packet
{
  public:
    NewEnemyPacket(std::size_t id = 0, EnemyType type = EnemyType::Boss)
        : Packet(PacketId::NEW_ENEMY), id(id), type(type)
    {
    }

    enum PacketMode getMode() const
    {
        return PacketMode::TCP;
    }

    void serialize()
    {
        this->write(id);
        this->write(type);
    }
    void unserialize()
    {
        this->read(id);
        this->read(type);
    }

    const std::string getName()
    {
        return "NewEnemyPacket";
    }

    PacketDisplay display() const
    {
        return {"Id", this->id};
    }

    std::shared_ptr<Packet> clone() const
    {
        return make_copy(NewEnemyPacket);
    }

    auto getEntityId() const -> std::size_t
    {
        return this->id;
    }

    auto getType() const -> EnemyType
    {
        return type;
    }

  private:
    std::size_t id;
    EnemyType type;
};

#endif /* NEWENEMY_PACKET_HPP */
