/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** client graphical lib
*/

#ifndef CLIENT_INPUTBOX_HPP
#define CLIENT_INPUTBOX_HPP

#include "Color.hpp"
#include <string>

namespace gl {
    class InputBox {
    public:
        virtual ~InputBox() = default;
        virtual auto draw() const -> void = 0;
        virtual auto update() -> void = 0;

        virtual auto onTextChange() -> void = 0;
        virtual auto getText() -> std::string = 0;
    protected:
        int x;
        int y;
        int width;
        int height;
        Color idleColor;
        Color selectedColor;

        std::string text;

        bool selected;
    };
}
#endif // CLIENT_INPUTBOX_HPP
