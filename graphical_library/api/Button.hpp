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
        MyButton(int x, int y, int width, int height, Color buttonColor,
            Color hoveredButtonColor, int transparency = 255);
        virtual ~Button() = 0;
        virtual auto ~Button() = 0;
        virtual auto Draw() const -> void = 0;
        virtual auto IsClicked() -> bool = 0;
        virtual auto IsHovered() -> bool = 0;
        virtual auto SetPosition(int x, int y) -> void = 0;
        virtual auto SetSize(int width, int height) -> void = 0;
        virtual auto SetTransparency(int transparency) -> void = 0;
        virtual auto SetColor(Color color) -> void = 0;
        virtual auto SetText(std::string str) -> void = 0;
        virtual auto SwitchClick() -> void = 0;
    };
}
#endif // BUTTON_HPP_
