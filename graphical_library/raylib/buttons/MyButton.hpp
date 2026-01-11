/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** client graphical lib
*/

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <graphical_library/api/MyButton.hpp>


class MyButton : public gl::Button
{
public:
    MyButton(int x, int y, int width, int height, Color buttonColor,
        Color hoveredButtonColor, int transparency = 255);
    void Draw() const override;
    void Update() override;
    bool IsClicked() override;
    bool IsHovered() override;
    void SetPosition(int x, int y) override;
    void SetSize(int width, int height) override;
    void SetTransparency(int transparency) override;
    void SetColor(Color color) override;
    void SetHoveredColor(Color aColor) override;
    void SetText(const std::string str) override;
    void SwitchClick() override;
private:
    bool hovered;
    int posX;
    int posY;
    int sizeX;
    int sizeY;
    Color color;
    Color hoveredColor;
    int transparency;
    std::string text;
    bool clicked = false;
};
#endif // BUTTON_HPP_
