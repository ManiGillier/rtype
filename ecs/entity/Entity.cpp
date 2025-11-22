#include "Entity.hpp"

Entity::Entity(size_t id) : _id(id) {}

Entity::operator size_t() const
{
    return _id;
}

bool Entity::operator==(Entity const& other) const
{
    return _id == other._id;
}

bool Entity::operator!=(Entity const& other) const
{
    return _id != other._id;
}
