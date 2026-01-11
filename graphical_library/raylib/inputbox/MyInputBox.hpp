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
    MyInputBox(int x, int y, int width, int height, Color boxColor,
        Color hoveredBoxColor, int transparency = 255);
    void Draw() const override;
    void Update() override;
    void SetPosition(int x, int y) override;
    void SetSize(int width, int height) override;
    void SetTransparency(int transparency) override;
    void SetColor(Color color) override;
    void SetHoveredColor(Color aColor) override;
    void SetText(const std::string& str) override;
    bool IsHovered();
    bool IsActive();
    void SetActive(bool active);
   std::string GetText(void) override;


private:
    bool hovered;
    bool active;
    int posX;
    int posY;
    int sizeX;
    int sizeY;
    Color color;
    Color hoveredColor;
    Color activeColor;
    int transparency;
    std::string text;
    int cursorPosition;
};
#endif // MYINPUTBOX_HPP
