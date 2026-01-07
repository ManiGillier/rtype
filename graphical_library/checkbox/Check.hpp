/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/

#ifndef CHECKBOX_H_
#define CHECKBOX_H_

class CheckBox : public ck::CheckBox
{
public:
    CheckBox(int x, int y, int size, bool checked = false, int transparency = 255);
    auto Draw() const -> void = 0;
    auto Update() -> void = 0;
    auto IsClicked() const -> bool = 0;
    auto IsHovered() const -> bool = 0;
    auto IsChecked() const -> bool = 0;
    auto SetChecked(bool checked) -> void = 0;
    auto Toggle() -> void = 0;
    auto SetPosition(int x, int y) -> void = 0;
    auto SetSize(int size) -> void = 0;
    auto SetTransparency(int transparency) -> void = 0;
    auto SetColor(Color color) -> void = 0;
    auto SetText(string str) -> void = 0;
    auto OnClick() -> void = 0;

private:
    bool hovered = 0;
    bool checked = 0;
    int posX;
    int posY;
    int size;
    int transparency;
    Color color;
    string text;
};
