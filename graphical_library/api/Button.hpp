/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** client graphical lib
*/

#ifndef CLIENT_BUTTON_HPP
#define CLIENT_BUTTON_HPP

#include "Color.hpp"
#include <string>

namespace gl {
    class Button {
    public:
        virtual ~Button() = default;
        virtual auto draw() const -> void = 0;
        virtual auto update() -> void = 0;

        virtual auto onClick() -> void = 0;
        virtual auto onHover() -> void = 0;
    protected:
        int x;
        int y;
        int width;
        int height;
        Color idleColor;
        Color hoverColor;
        Color pressedColor;

        std::string text;

        bool clicked = false;
        bool hovered = false;

        enum TextAlign {
          CENTER,
          LEFT,
          RIGHT
        };
        TextAlign alignment = CENTER;
    };
}
#endif // BUTTON_HPP_
