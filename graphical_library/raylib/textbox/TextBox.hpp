/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** client graphical lib
*/

#ifndef MYTEXTBOX_HPP
#define MYTEXTBOX_HPP
#include <graphical_library/api/TextBox.hpp>

class TextBox : public gl::TextBox
{
public:
    TextBox();
    void draw() const;
    void update();
};
#endif // MYTEXTBOX_HPP
