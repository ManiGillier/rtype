/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** client graphical lib
*/

#ifndef MYINPUTBOX_HPP
#define MYINPUTBOX_HPP
#include <graphical_library/api/MyInputBox.hpp>

class MyInputBox : public gl::InputBox
{
public:
    MyInputBox(int x, int y, int width, int height, gl::Color boxColor,
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
   std::string getText(void) override;


private:
    bool hovered;
    bool active;
    int posX;
    int posY;
    int sizeX;
    int sizeY;
    gl::Color color;
    gl::Color hoveredColor;
    gl::Color activeColor;
    int transparency;
    std::string text;
    int cursorPosition;
};
#endif // MYINPUTBOX_HPP
