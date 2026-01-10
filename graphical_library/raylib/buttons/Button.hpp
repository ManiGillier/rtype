/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** client graphical lib
*/

#ifndef BUTTON_HPP
#define BUTTON_HPP

namespace bt {
    class Button {
    public:
        Button(int x, int y, int width, int height, int transparency = 255);
        virtual auto Draw() const -> void = 0;
        virtual auto Update() -> void = 0;
        virtual auto IsClicked() const -> bool = 0;
        virtual auto IsHovered() const -> bool = 0;
        virtual auto SetPosition(int x, int y) -> void = 0;
        virtual auto SetSize(int width, int height) -> void = 0;
        virtual auto SetTransparency(int transparency) -> void = 0;
        virtual auto SetColor(Color color) -> void = 0;
        virtual auto SetText(string str) -> void = 0;
        virtual auto OnClick() -> void = 0;
    private:
        bool hovered;
        int posX;
        int posY;
        int sizeX;
        int sizeY;
        int transparency;
        Color color;
        string text;
    };
}
#endif // BUTTON_HPP_
