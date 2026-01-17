/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** ScoreExecutor
*/

#ifndef SCOREEXECUTOR_HPP_
    #define SCOREEXECUTOR_HPP_

#include "../../player/Player.hpp"
#include <network/packets/PacketManager.hpp>
#include <network/packets/impl/ScorePacket.hpp>
#include <network/server/Server.hpp>
#include <memory>

class RTypeServer;

class ScoreExecutor
    : public PacketExecutorImplServer<ScorePacket, Player>
{
  public:
    ScoreExecutor(RTypeServer &server);
    ~ScoreExecutor() = default;
    bool execute(Server &server, std::shared_ptr<Player> player,
                 std::shared_ptr<ScorePacket> packet);
    int getPacketId() const {
        return PacketId::SCORE_PACKET;
    }

  private:
    RTypeServer &_rtypeServer;
};
#endif /* !SCOREEXECUTOR_HPP_ */
