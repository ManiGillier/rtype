/*
** EPITECH PROJECT, 2026
** rtype [WSL: Ubuntu-24.04]
** File description:
** RCONRequestExecutor
*/

#ifndef RCONREQUESTEXECUTOR_HPP_
#define RCONREQUESTEXECUTOR_HPP_

#include "../../player/Player.hpp"
#include <network/packets/PacketManager.hpp>
#include <network/packets/impl/RCONRequest.hpp>
#include <network/server/Server.hpp>
#include <memory>

#define HERE_IS_THE_LIST_OF_PLAYERS "Here is the current list of all the connected players: "
#define HERE_IS_THE_BANLIST "Here is the current list of all banned players: "
#define NO_SUCH_PLAYER_ONLINE "No such player currently online: "
#define NO_SUCH_PLAYER_REGISTERED "No such player registered: "
#define PLAYER_IS_ALREADY_BANNED "This player is already banned: "
#define PLAYER_IS_NOT_BANNED "This player is not banned: "
#define SUCCESSFULLY_KICKED "Succesfully kicked player: "
#define SUCCESSFULLY_BANNED "Succesfully banned player: "
#define SUCCESSFULLY_UNBANNED "Succesfully unbanned player: "

class RTypeServer;

class RCONRequestExecutor
    : public PacketExecutorImplServer<RCONRequest, Player>
{
  public:
    RCONRequestExecutor(RTypeServer &server);
    ~RCONRequestExecutor() = default;
    bool execute(Server &server, std::shared_ptr<Player> player,
                 std::shared_ptr<RCONRequest> packet);
    int getPacketId() const {
        return PacketId::RCON_REQUEST;
    }

  private:
    void kick(std::shared_ptr<Player> player, const std::string &target);
    void ban(std::shared_ptr<Player> player, const std::string &target);
    void unban(std::shared_ptr<Player> player, const std::string &target);
    void banlist(std::shared_ptr<Player> player);
    void list(std::shared_ptr<Player> player);
    RTypeServer &_rtypeServer;
};

#endif /* !RCONREQUESTEXECUTOR_HPP_ */
