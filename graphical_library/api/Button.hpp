/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** client graphical lib
*/

#ifndef CLIENT_BUTTON_HPP
#define CLIENT_BUTTON_HPP

namespace bt {
    class Button {
    public:
        Button(int x, int y, int width, int height, int transparency = 255);
        virtual ~Button() = 0;
        virtual auto ~Button() = 0;
        virtual auto Draw() const -> void = 0;
        virtual auto IsClicked() const -> bool = 0;
        virtual auto IsHovered() const -> bool = 0;
        virtual auto SetPosition(int x, int y) -> void = 0;
        virtual auto SetSize(int width, int height) -> void = 0;
        virtual auto SetTransparency(int transparency) -> void = 0;
        virtual auto SetColor(Color color) -> void = 0;
        virtual auto SetText(string str) -> void = 0;
        virtual auto OnClick() -> void = 0;
    };
}
#endif // BUTTON_HPP_
