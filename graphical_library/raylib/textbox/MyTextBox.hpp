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
    MyTextBox(int x, int y, int width, int height, Color boxColor,
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
    int cursorPosition;
};
#endif // MYTEXTBOX_HPP
