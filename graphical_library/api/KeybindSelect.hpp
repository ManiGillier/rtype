/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** client graphical lib
*/

#ifndef CLIENT_KEYBINDSELECT_HPP
#define CLIENT_KEYBINDSELECT_HPP

#include "Color.hpp"
#include <string>

namespace gl {
    class KeybindSelect {
    public:
        virtual ~KeybindSelect() = default;
        virtual auto draw() const -> void = 0;
        virtual auto update() -> void = 0;

        virtual auto onKeybindSet() -> void = 0;
        virtual auto getKey() -> int = 0;
    protected:
        int x;
        int y;
        int width;
        int height;
        Color idleColor;
        Color selectedColor;

        int key;

        bool selected = false;
    };
}
#endif // CLIENT_KEYBINDSELECT_HPP
