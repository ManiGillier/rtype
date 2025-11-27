/*
** EPITECH PROJECT, 2025
** server [WSL: Ubuntu-24.04]
** File description:
** Object
*/

#ifndef OBJECT_HPP_
    #define OBJECT_HPP_

    #include "Position.hpp"

class Object {
    public:
        enum ObjectType {EMPTY = 0, COIN, ZAP, FINISH};
        Object(ObjectType objectType = EMPTY, int x = 0, int y = 0);
        int getX() const;
        int getY() const;
        const Position &getPosition() const;
        enum ObjectType getType() const;
    private:
        Position pos;
        enum ObjectType objectType;
};

#endif /* !OBJECT_HPP_ */
