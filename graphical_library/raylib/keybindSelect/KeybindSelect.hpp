/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** client graphical lib
*/

#ifndef MYKEYBINDSELECT_HPP
#define MYKEYBINDSELECT_HPP
#include <graphical_library/api/KeybindSelect.hpp>

class KeybindSelect : public gl::KeybindSelect
{
public:
    KeybindSelect();
    auto draw() const -> void;
    auto update() -> void;

    inline virtual auto onKeybindSet() -> void {}
    auto getKey() -> int;
};
#endif // MYKEYBINDSELECT_HPP
