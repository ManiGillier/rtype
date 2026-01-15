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
        virtual auto setPosition(int x, int y) -> void = 0;
        virtual auto setSize(int width, int height) -> void = 0;
        virtual auto setTransparency(int transparency) -> void = 0;
        virtual auto setColor(Color aColor) -> void = 0;
        virtual auto setHoveredColor(Color aColor) -> void = 0;
        virtual auto setText(const std::string& str) -> void = 0;
        virtual auto getText(void) -> std::string = 0;
    };
}
#endif // CLIENT_INPUTBOX_HPP
