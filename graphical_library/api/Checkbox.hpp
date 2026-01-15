/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/

#ifndef CLIENT_CHECKBOX_HPP
#define CLIENT_CHECKBOX_HPP
#include "Color.hpp"
#include <string>

namespace gl {
    class Checkbox {
    public:
        virtual ~Checkbox() = default;
        virtual auto draw() const -> void = 0;
        virtual auto update() -> void = 0;

        virtual auto onCheck() -> void = 0;
        virtual auto onUncheck() -> void = 0;
        virtual auto isChecked() const -> bool = 0;
    protected:
        int x;
        int y;
        int size;
        Color backgroundColor;
        Color idleColor;
        Color hoverColor;
        Color pressedColor;
        Color checkedColor;

        std::string text;

        bool clicked;
        bool hovered;
        bool checked;
    };
}
#endif
