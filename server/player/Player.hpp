/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** player
*/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "network/server/Server.hpp"
#include "network/server/Server.hpp"

class Player : public ServerClient
{
  public:
    Player(int fd, Server &s, std::size_t id);
    ~Player() = default;
    std::size_t getId() const;
    void setLobby(const std::string &lobbyid);
    const std::string &getLobbyId() const;

  private:
    std::size_t _id;
    std::string _lobbyId;
};

#endif /* PLAYER_HPP */
