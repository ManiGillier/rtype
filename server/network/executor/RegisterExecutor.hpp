/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** RegisterExecutor
*/

#ifndef REGISTEREXECUTOR_HPP_
    #define REGISTEREXECUTOR_HPP_

#include "../../player/Player.hpp"
#include <network/packets/PacketManager.hpp>
#include <network/packets/impl/RegisterPacket.hpp>
#include <network/server/Server.hpp>
#include <memory>

#define EMPTY_USERNAME_OR_PASSWORD "tried to register with empty username or password, disconnecting.."
#define PASSWORD_USED_BY "Sorry, password is already being used by user "

class RTypeServer;

class RegisterExecutor
    : public PacketExecutorImplServer<RegisterPacket, Player>
{
  public:
    RegisterExecutor(RTypeServer &server);
    ~RegisterExecutor() = default;
    bool execute(Server &server, std::shared_ptr<Player> player,
                 std::shared_ptr<RegisterPacket> packet);
    int getPacketId() const {
        return PacketId::REGISTER_PACKET;
    }

    std::string usernameListToString(const std::vector<std::string> &usernames) const {
        std::string string = "";

        for (std::size_t i = 0; i < usernames.size(); i++) {
            if (i + 1 != usernames.size())
                string += ", ";
            string += usernames[i];
        }
        return string;
    }

  private:
    RTypeServer &_rtypeServer;
};

#endif /* !REGISTEREXECUTOR_HPP_ */
