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
    MyButton(int x, int y, int width, int height, gl::Color buttonColor,
        gl::Color hoveredButtonColor, int transparency = 255);
    virtual void draw() const override;
    virtual void update() override;
    bool isClicked() override;
    bool isHovered() override;
    void setPosition(int x, int y) override;
    void setSize(int width, int height) override;
    void setTransparency(int transparency) override;
    void setColor(gl::Color color) override;
    void setHoveredColor(gl::Color aColor) override;
    void setText(const std::string str) override;
    void switchClick() override;
private:
    bool hovered;
    int posX;
    int posY;
    int sizeX;
    int sizeY;
    gl::Color color;
    gl::Color hoveredColor;
    int transparency;
    std::string text;
    bool clicked = false;
};
#endif // BUTTON_HPP_
