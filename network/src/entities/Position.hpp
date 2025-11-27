/*
** EPITECH PROJECT, 2025
** server [WSL: Ubuntu-24.04]
** File description:
** Position
*/

#ifndef POSITION_HPP_
    #define POSITION_HPP_

class Position {
    public:
        Position(int x, int y);
        int getX() const;
        int getY() const;
    private:
        int x;
        int y;
};

#endif /* !POSITION_HPP_ */
