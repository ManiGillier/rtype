/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** TextChatString executor
*/

#ifndef TEXTCHATSTRING_EXECUTOR_HPP
#define TEXTCHATSTRING_EXECUTOR_HPP

#include "client/state_machine/states/game/Game.hpp"

#include <memory>
#include <network/packets/listener/PacketExecutor.hpp>
#include <network/packets/impl/TextChatStringPacket.hpp>

class TextChatStringExecutorGame : public PacketExecutorImplClient
<TextChatStringPacket, ClientPollable>
{
public:
    TextChatStringExecutorGame(Game &state) : state(state) {}

    bool execute([[maybe_unused]]Client &cl,
                 [[maybe_unused]] std::shared_ptr<ClientPollable> con,
                 [[maybe_unused]] std::shared_ptr<TextChatStringPacket> packet)
    {
        this->state.addChatMessage(packet->getStr());
        return true;
    }

    int getPacketId() const {
        return PacketId::TEXT_CHAT_STRING_PACKET;
    }
private:
    [[maybe_unused]] Game &state;
};

#endif /* TEXTCHATSTRING_EXECUTOR_HPP */
