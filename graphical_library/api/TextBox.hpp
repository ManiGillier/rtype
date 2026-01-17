/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** client graphical lib
*/

#ifndef CLIENT_TEXTBOX_HPP
#define CLIENT_TEXTBOX_HPP

#include "Color.hpp"
#include <string>

namespace gl {
    class TextBox {
    public:
        virtual ~TextBox() = default;
        virtual auto draw() const -> void = 0;
        virtual auto update() -> void = 0;
    protected:
        int x;
        int y;
        int width;
        int height;
        Color color;
        Color cColor = {0, 0, 0, 255};
        float lineThickness = 1;
        std::string text;
        enum TextAlign {
          CENTER,
          LEFT,
          RIGHT
        };
        TextAlign alignment = CENTER;
    };
}
#endif // TEXTBOX_HPP_
