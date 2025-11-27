/*
** EPITECH PROJECT, 2025
** server [WSL: Ubuntu-24.04]
** File description:
** Position
*/

#include "Position.hpp"

Position::Position(int x, int y)
{
    this->x = x;
    this->y = y;
}

int Position::getX() const
{
    return this->x;
}

int Position::getY() const
{
    return this->y;
}
