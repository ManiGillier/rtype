/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/

#ifndef CHECKBOX_H_
#define CHECKBOX_H_

#include <graphical_library/api/Checkbox.hpp>
#include <string>

class Checkbox : public gl::Checkbox
{
public:
    Checkbox();
    auto draw() const -> void;
    auto update() -> void;

    inline virtual auto onCheck() -> void {}
    inline virtual auto onUncheck() -> void {}
    auto isChecked() const -> bool;
};

#endif
