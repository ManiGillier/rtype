/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** client graphical lib
*/

#ifndef MYTEXTBOX_HPP
#define MYTEXTBOX_HPP
#include <graphical_library/api/MyTextBox.hpp>

class MyTextBox : public gl::TextBox
{
public:
    MyTextBox(int x, int y, int width, int height, gl::Color boxColor,
        gl::Color hoveredBoxColor, int transparency = 255);
    void draw() const override;
    void update() override;
    void setPosition(int x, int y) override;
    void setSize(int width, int height) override;
    void setTransparency(int transparency) override;
    void setColor(gl::Color color) override;
    void setHoveredColor(gl::Color aColor) override;
    void setText(const std::string& str) override;
    bool isHovered();
    bool isActive();
    void setActive(bool active);

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
    int cursorPosition;
};
#endif // MYTEXTBOX_HPP
