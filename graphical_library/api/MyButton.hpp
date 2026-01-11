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
        virtual auto Draw() const -> void = 0;
        virtual auto Update() -> void = 0;
        virtual auto IsClicked() -> bool = 0;
        virtual auto IsHovered() -> bool = 0;
        virtual auto SetPosition(int x, int y) -> void = 0;
        virtual auto SetSize(int width, int height) -> void = 0;
        virtual auto SetTransparency(int transparency) -> void = 0;
        virtual auto SetColor(Color aColor) -> void = 0;
        virtual auto SetHoveredColor(Color aColor) -> void = 0;
        virtual auto SetText(const std::string str) -> void = 0;
        virtual auto SwitchClick() -> void = 0;
    };
}
#endif // BUTTON_HPP_
