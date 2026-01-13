/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/

#include "MyTextBox.hpp"
#include <raylib.h>

MyTextBox::MyTextBox(int x, int y, int width, int height,
    Color boxColor, Color hoveredBoxColor, int transparency)
    : hovered(false), posX(x), posY(y), sizeX(width), sizeY(height),
    color(boxColor), hoveredColor(hoveredBoxColor),
    transparency(transparency), text(""), cursorPosition(0) {}

void MyTextBox::draw() const {
    Rectangle boxRect = {
        static_cast<float>(posX),
        static_cast<float>(posY),
        static_cast<float>(sizeX),
        static_cast<float>(sizeY)
    };

    Color currentColor = this->hovered ? this->hoveredColor : this->color;
    DrawRectangleRec(boxRect, currentColor);

    if (this->hovered)
        DrawRectangleLinesEx(boxRect, 2, DARKGRAY);
    else
        DrawRectangleLinesEx(boxRect, 1, BLACK);

    if (!this->text.empty()) {
        DrawText(
            this->text.c_str(),
            this->posX + 10,
            this->posY + (this->sizeY / 2) - 10,
            20,
            BLACK
        );
    }
}

void MyTextBox::update()
{
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();

    if (((this->posX < mouseX) && (this->posX + this->sizeX > mouseX)) && ((this->posY < mouseY) && (this->posY + this->sizeY > mouseY)))
        this->hovered = true;
    else
        this->hovered = false;
}

bool MyTextBox::isHovered() {

    return this->hovered;
}

void MyTextBox::setPosition(int x, int y) {
    this->posX = x;
    this->posY = y;
}

void MyTextBox::setSize(int width, int height) {
    this->sizeX = width;
    this->sizeY = height;
}

void MyTextBox::setTransparency(int transparency) {
    this->transparency = transparency;
}

void MyTextBox::setColor(Color color) {
    this->color = color;
}

void MyTextBox::setHoveredColor(Color aColor) {
    this->hoveredColor = aColor;
}

void MyTextBox::setText(const std::string& str) {
    this->text = str;
    this->cursorPosition = (int)this->text.length();
}
