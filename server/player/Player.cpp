#include "Player.hpp"
#include "network/server/ServerClient.hpp"

Player::Player(int fd, PollManager &pm, int id) : ServerClient(fd, pm), _id(id)
{
}

int Player::getId() const 
{
    return _id;
}
