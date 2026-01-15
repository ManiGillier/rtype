#include "Player.hpp"

Player::Player(int fd, Server &s, std::size_t id, std::optional<std::size_t> entityId)
    : ServerClient(fd, s), _id(id), _entityId(entityId)
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

void Player::setEntityId(std::optional<std::size_t> entityId)
{
    this->_entityId = entityId;
}

std::optional<std::size_t> Player::getEntityId() const
{
    return this->_entityId;
}

void Player::setConnected(bool connected)
{
    this->connected = connected;
}

bool Player::isConnected() const
{
    return this->connected;
}

const std::string &Player::getUsername() const
{
    return this->username;
}

void Player::setUsername(const std::string &username)
{
    this->username = username;
}

void Player::connect(const std::string &username)
{
    this->setConnected(true);
    this->setUsername(username);
}
