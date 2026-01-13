/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/

#ifndef CHECKBOX_H_
#define CHECKBOX_H_

#include <graphical_library/api/MyCheck.hpp>
#include <string>
#include <raylib.h>

class MyCheckBox : public gl::Checkbox
{
public:
    MyCheckBox(int x, int y, int size, bool checked = false, int transparency = 255);
    void draw() const override;
    void update() override;
    bool isClicked() override;
    bool isHovered() override;
    bool isChecked() const override;
    void setChecked(bool checked) override;
    void toggle() override;
    void setPosition(int x, int y) override;
    void setSize(int size) override;
    void setTransparency(int transparency) override;
    void setColor(Color aColor) override;
    void setHoveredColor(Color aColor) override;
    void setText(const std::string& str) override;
    void onClick() override;
private:
    bool hovered = 0;
    bool checked = 0;
    int posX;
    int posY;
    int size;
    int transparency;
    Color color;
    Color hoveredColor;
    std::string text;
};

#endif
