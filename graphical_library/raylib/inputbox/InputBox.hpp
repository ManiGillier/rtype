/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** client graphical lib
*/

#ifndef MYINPUTBOX_HPP
#define MYINPUTBOX_HPP
#include <graphical_library/api/InputBox.hpp>

class InputBox : public gl::InputBox
{
public:
    InputBox();
    auto draw() const -> void;
    auto update() -> void;

    inline virtual auto onTextChange() -> void {}
    inline virtual auto onValidation() -> void {}
    auto getText() -> std::string;
};
#endif // MYINPUTBOX_HPP
