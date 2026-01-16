/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** client graphical lib
*/

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <graphical_library/api/Button.hpp>

class Button : public gl::Button
{
public:
    Button();
    auto draw() const -> void;
    auto update() -> void;

    inline virtual auto onClick() -> void {}
    inline virtual auto onHover() -> void {}
private:
};
#endif // BUTTON_HPP_
