#include "Player.hpp"

Player::Player(int fd, Server &s, std::size_t id)
    : ServerClient(fd, s), _id(id)
{
}

std::size_t Player::getId() const
{
    return _id;
}


void Player::setLobby(const std::string &lobbyid)
{
    this->_lobbyId = lobbyid;
}

const std::string &Player::getLobbyId() const
{
    return this->_lobbyId;
}
