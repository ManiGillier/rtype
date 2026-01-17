/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** TextChatStringExecutor
*/

#ifndef TEXT_CHAT_STRING_EXEC_HPP_
#define TEXT_CHAT_STRING_EXEC_HPP_

#include "../../player/Player.hpp"
#include <memory>
#include <network/packets/PacketManager.hpp>
#include <network/packets/impl/TextChatStringPacket.hpp>
#include <network/server/Server.hpp>

class RTypeServer;

class TextChatStringExecutor
    : public PacketExecutorImplServer<TextChatStringPacket, Player>
{
  public:
    TextChatStringExecutor(RTypeServer &server) : _rtypeServer(server) {};
    ~TextChatStringExecutor() = default;
    bool execute(Server &server, std::shared_ptr<Player> player,
                 std::shared_ptr<TextChatStringPacket> packet);

    int getPacketId() const
    {
        return PacketId::TEXT_CHAT_STRING_PACKET;
    }

  private:
    RTypeServer &_rtypeServer;
};
#endif /* !TEXT_CHAT_STRING_EXEC_HPP_ */
