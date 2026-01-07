/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/

#ifndef CHECKBOX_H_
#define CHECKBOX_H_

namespace ck {
    class CheckBox {
    public:
        CheckBox(int x, int y, int size, bool checked = false, int transparency = 255);
        virtual auto Draw() const -> void = 0;
        virtual auto Update() -> void = 0;
        virtual auto IsClicked() const -> bool = 0;
        virtual auto IsHovered() const -> bool = 0;
        virtual auto IsChecked() const -> bool = 0;
        virtual auto SetChecked(bool checked) -> void = 0;
        virtual auto Toggle() -> void = 0;
        virtual auto SetPosition(int x, int y) -> void = 0;
        virtual auto SetSize(int size) -> void = 0;
        virtual auto SetTransparency(int transparency) -> void = 0;
        virtual auto SetColor(Color color) -> void = 0;
        virtual auto SetText(string str) -> void = 0;
        virtual auto OnClick() -> void = 0;

    private:
        bool hovered;
        bool checked;
        int posX;
        int posY;
        int size;
        int transparency;
        Color color;
        string text;
    };
}
