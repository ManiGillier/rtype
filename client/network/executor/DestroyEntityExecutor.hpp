/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** DestroyEntity executor
*/

#ifndef DESTROYENTITY_EXECUTOR_HPP
#define DESTROYENTITY_EXECUTOR_HPP

#include "client/state_machine/states/game/Game.hpp"

#include <memory>
#include <network/packets/listener/PacketExecutor.hpp>
#include <network/packets/impl/DestroyEntityPacket.hpp>

class DestroyEntityExecutor : public PacketExecutorImplClient
<DestroyEntityPacket, ClientPollable>
{
public:
    DestroyEntityExecutor(Game &state) : state(state) {}

    bool execute([[maybe_unused]]Client &cl,
                 [[maybe_unused]] std::shared_ptr<ClientPollable> con,
                 [[maybe_unused]] std::shared_ptr<DestroyEntityPacket> packet)
    {
        this->state.destroyEntities(packet->getIds());
        return true;
    }

    int getPacketId() const {
        return PacketId::DESTROY_ENTITY_PACKET;
    }
private:
    [[maybe_unused]] Game &state;
};

#endif /* DESTROYENTITY_EXECUTOR_HPP */
