/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** client graphical lib
*/

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <graphical_library/api/Button.hpp>

class Button : bt::Button
{
public:
    Button(int x, int y, int width, int height, int transparency = 255);
    auto Draw() const -> void = 0;
    auto IsClicked() const -> bool = 0;
    auto IsHovered() const -> bool = 0;
    auto SetPosition(int x, int y) -> void = 0;
    auto SetSize(int width, int height) -> void = 0;
    auto SetTransparency(int transparency) -> void = 0;
    auto SetColor(Color color) -> void = 0;
    auto SetText(string str) -> void = 0;
    auto OnClick() -> void = 0;
private:
    bool hovered;
    int posX;
    int posY;
    int sizeX;
    int sizeY;
    int transparency;
    Color color;
    string text;
    bool clicked = false;
};
#endif // BUTTON_HPP_
