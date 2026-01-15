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
#include <cstddef>
#include <optional>

class Player : public ServerClient
{
  public:
    Player(int fd, Server &s, std::size_t id, std::optional<std::size_t> entityId);
    ~Player() = default;
    std::size_t getId() const;
    void setLobby(const std::string &lobbyid);
    const std::string &getLobbyId() const;
    void setEntityId(std::optional<std::size_t> entityId);
    std::optional<std::size_t> getEntityId() const;
    void setConnected(bool connected);
    bool isConnected() const;
    const std::string &getUsername() const;
    void setUsername(const std::string &username);
    void connect(const std::string &username);

  private:
    std::size_t _id;
    std::optional<std::size_t> _entityId;
    std::string _lobbyId;
    bool connected = false;
    std::string username = "";
};

#endif /* PLAYER_HPP */
