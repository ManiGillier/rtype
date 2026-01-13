/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** client graphical lib
*/

#ifndef CLIENT_TEXTBOX_HPP
#define CLIENT_TEXTBOX_HPP

#include <raylib.h>
#include <string>

namespace gl {
    class TextBox {
    public:
        virtual ~TextBox() = default;
        virtual auto draw() const -> void = 0;
        virtual auto update() -> void = 0;
        virtual auto setPosition(int x, int y) -> void = 0;
        virtual auto setSize(int width, int height) -> void = 0;
        virtual auto setTransparency(int transparency) -> void = 0;
        virtual auto setColor(Color aColor) -> void = 0;
        virtual auto setHoveredColor(Color aColor) -> void = 0;
        virtual auto setText(const std::string& str) -> void = 0;
    };
}
#endif // TEXTBOX_HPP_
