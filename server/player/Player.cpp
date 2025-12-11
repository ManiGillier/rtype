#include "Player.hpp"
#include "network/server/ServerClient.hpp"

Player::Player(int fd, PollManager &pm, int id)
    : ServerClient(fd, pm), _id(id), _ready(false)
{
}

int Player::getId() const
{
    return _id;
}

void Player::setReady()
{
    _ready = true;
}

bool Player::isReady() const
{
    return _ready;
}
