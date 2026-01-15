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
        virtual auto isClicked() -> bool = 0;
        virtual auto isHovered() -> bool = 0;
        virtual auto isChecked() const -> bool = 0;
        virtual auto setChecked(bool checked) -> void = 0;
        virtual auto toggle() -> void = 0;
        virtual auto setPosition(int x, int y) -> void = 0;
        virtual auto setSize(int size) -> void = 0;
        virtual auto setTransparency(int transparency) -> void = 0;
        virtual auto setColor(Color color) -> void = 0;
        virtual auto setHoveredColor(Color aColor) -> void = 0;
        virtual auto setText(const std::string& str) -> void = 0;
        virtual auto onClick() -> void = 0;
    };
}
#endif
