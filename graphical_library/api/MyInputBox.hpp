/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** client graphical lib
*/

#ifndef CLIENT_INPUTBOX_HPP
#define CLIENT_INPUTBOX_HPP

#include <raylib.h>
#include <string>

namespace gl {
    class InputBox {
    public:
        virtual ~InputBox() = default;
        virtual auto Draw() const -> void = 0;
        virtual auto Update() -> void = 0;
        virtual auto SetPosition(int x, int y) -> void = 0;
        virtual auto SetSize(int width, int height) -> void = 0;
        virtual auto SetTransparency(int transparency) -> void = 0;
        virtual auto SetColor(Color aColor) -> void = 0;
        virtual auto SetHoveredColor(Color aColor) -> void = 0;
        virtual auto SetText(const std::string& str) -> void = 0;
        virtual auto GetText(void) -> std::string = 0;
    };
}
#endif // CLIENT_INPUTBOX_HPP
