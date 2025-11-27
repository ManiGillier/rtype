/*
** EPITECH PROJECT, 2025
** server [WSL: Ubuntu-24.04]
** File description:
** Object
*/

#include "Object.hpp"

Object::Object(ObjectType objectType, int x, int y) : pos(x, y)
{
    this->objectType = objectType;
}

int Object::getX() const
{
    return pos.getX();
}

int Object::getY() const
{
    return pos.getY();
}

const Position &Object::getPosition() const
{
    return this->pos;
}

Object::ObjectType Object::getType() const
{
    return this->objectType;
}
