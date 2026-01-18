/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** client graphical lib
*/

#ifndef MYKEYBINDSELECT_HPP
#define MYKEYBINDSELECT_HPP
#include <graphical_library/api/Key.hpp>
#include <graphical_library/api/KeybindSelect.hpp>
#include <graphical_library/api/GraphicalLibrary.hpp>

class KeybindSelect : public gl::KeybindSelect
{
public:
    KeybindSelect(gl::GraphicalLibrary &gl);
    auto draw() const -> void;
    auto update() -> void;

    inline virtual auto onKeybindSet() -> void {}
    auto getKey() -> gl::Key;
private:
    gl::GraphicalLibrary &gl;
};
#endif // MYKEYBINDSELECT_HPP
