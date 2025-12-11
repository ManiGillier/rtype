/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** player
*/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <network/server/ServerClient.hpp>

class Player : public ServerClient
{
  public:
    Player(int fd, PollManager &pm, int id);
    ~Player() = default;
    int getId() const;
    void setReady();
    bool isReady() const;

  private:
    int _id;
    bool _ready;
};

#endif /* PLAYER_HPP */
