/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** client graphical lib
*/

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <graphical_library/api/Button.hpp>

class MyButton : bt::Button
{
public:
    MyButton(int x, int y, int width, int height, Color buttonColor,
        Color hoveredButtonColor, int transparency = 255);
    void Draw() const;
    bool IsClicked();
    bool IsHovered(int mouseX, int mouseY);
    void SetPosition(int x, int y);
    void SetSize(int width, int height);
    void SetTransparency(int transparency);
    void SetColor(Color color);
    void SetText(std::string str);
    void SwitchClick();
private:
    bool hovered;
    int posX;
    int posY;
    int sizeX;
    int sizeY;
    int transparency;
    Color color;
    Color hoveredColor;
    std::string text;
    bool clicked = false;
};
#endif // BUTTON_HPP_
