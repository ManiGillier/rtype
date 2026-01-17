/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** client graphical lib
*/

#ifndef MYBOX_HPP
#define MYBOX_HPP
#include <graphical_library/api/Box.hpp>

class Box : public gl::Box
{
public:
    Box();
    void draw() const;
    void update();
};
#endif // MYBOX_HPP
