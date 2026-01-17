/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** Text chat string
*/

#ifndef TEXT_CHAT_STRING_PACKET_HPP
#define TEXT_CHAT_STRING_PACKET_HPP

#include "network/packets/Packet.hpp"
#include <memory>

class TextChatStringPacket : public Packet
{
  public:
    TextChatStringPacket(std::string str = "")
        : Packet(PacketId::TEXT_CHAT_STRING_PACKET), str(str)
    {
    }

    enum PacketMode getMode() const
    {
        return PacketMode::TCP;
    }

    void serialize()
    {
        this->write(str);
    }
    void unserialize()
    {
        this->read(str);
    }

    const std::string getName()
    {
        return "TextChatStringPacket";
    }

    PacketDisplay display() const
    {
        return {"message:", this->str};
    }

    std::shared_ptr<Packet> clone() const
    {
        return make_copy(TextChatStringPacket);
    }

    auto getStr() const -> std::string
    {
        return this->str;
    }

  private:
    std::string str;
};

#endif /* TEXT_CHAT_STRING_PACKET_HPP */
