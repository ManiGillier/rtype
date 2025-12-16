#include "Player.hpp"

Player::Player(int fd, Server &s, std::size_t id)
    : ServerClient(fd, s), _id(id)
{
}

std::size_t Player::getId() const
{
    return _id;
}
