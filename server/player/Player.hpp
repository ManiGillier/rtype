/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** player
*/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "network/server/Server.hpp"
#include <cstddef>
#include <optional>

class RTypeServer;

class Player : public ServerClient
{
  public:
    Player(int fd, Server &s, std::size_t id,
           std::optional<std::pair<std::size_t, std::size_t>> entityId);
    ~Player() = default;
    std::size_t getId() const;
    void setLobby(const std::string &lobbyid);
    const std::string &getLobbyId() const;
    void setEntityId(std::optional<std::pair<std::size_t, std::size_t>>);
    std::optional<std::pair<std::size_t, std::size_t>> getEntityId() const;
    void setConnected(bool connected);
    bool isConnected() const;
    const std::string &getUsername() const;
    void setUsername(const std::string &username);
    void connect(const std::string &username);
    int getScore() const;
    void setScore(int newScore);
    void addScore(int toAdd);
    void saveScore(RTypeServer &srv) const;

  private:
    int score;
    std::size_t _id;
    std::optional<std::pair<std::size_t, std::size_t>> _entityId;
    std::string _lobbyId;
    bool connected = false;
    std::string username = "";
};

#endif /* PLAYER_HPP */
