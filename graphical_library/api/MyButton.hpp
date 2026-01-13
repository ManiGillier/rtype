/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** client graphical lib
*/

#ifndef CLIENT_BUTTON_HPP
#define CLIENT_BUTTON_HPP

#include <raylib.h>
#include <string>

namespace gl {
    class Button {
    public:
        virtual ~Button() = default;
        virtual auto draw() const -> void = 0;
        virtual auto update() -> void = 0;
        virtual auto isClicked() -> bool = 0;
        virtual auto isHovered() -> bool = 0;
        virtual auto setPosition(int x, int y) -> void = 0;
        virtual auto setSize(int width, int height) -> void = 0;
        virtual auto setTransparency(int transparency) -> void = 0;
        virtual auto setColor(Color aColor) -> void = 0;
        virtual auto setHoveredColor(Color aColor) -> void = 0;
        virtual auto setText(const std::string str) -> void = 0;
        virtual auto switchClick() -> void = 0;
    };
}
#endif // BUTTON_HPP_
