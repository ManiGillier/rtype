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
    : hovered(false), active(false), posX(x), posY(y), sizeX(width), sizeY(height),
    color(boxColor), hoveredColor(hoveredBoxColor),
    transparency(transparency), text(""), cursorPosition(0) {}

void MyTextBox::Draw() const {
    Rectangle boxRect = {
        static_cast<float>(posX),
        static_cast<float>(posY),
        static_cast<float>(sizeX),
        static_cast<float>(sizeY)
    };

    Color currentColor = this->active ? this->hoveredColor : this->color;

    DrawRectangleRec(boxRect, currentColor);

    if (this->active)
        DrawRectangleLinesEx(boxRect, 3, RED);
    else if (this->hovered)
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
    } else {
        DrawText(
            "Type here...",
            this->posX + 10,
            this->posY + (this->sizeY / 2) - 10,
            20,
            GRAY
        );
    }

    if (this->active) {
        int textWidth = MeasureText(this->text.c_str(), 20);
        DrawRectangle(
            this->posX + 10 + textWidth,
            this->posY + 10,
            2,
            this->sizeY - 20,
            BLACK
        );
    }
}

bool MyTextBox::IsHovered(int mouseX, int mouseY) {
    if (((this->posX < mouseX) && (this->posX + this->sizeX > mouseX)) && ((this->posY < mouseY) && (this->posY + this->sizeY > mouseY)))
        this->hovered = true;
    else
        this->hovered = false;
    return this->hovered;
}

bool MyTextBox::IsActive() {
    return this->active;
}

void MyTextBox::SetActive(bool active) {
    this->active = active;
}

void MyTextBox::SetPosition(int x, int y) {
    this->posX = x;
    this->posY = y;
}

void MyTextBox::SetSize(int width, int height) {
    this->sizeX = width;
    this->sizeY = height;
}

void MyTextBox::SetTransparency(int transparency) {
    this->transparency = transparency;
}

void MyTextBox::SetColor(Color color) {
    this->color = color;
}

void MyTextBox::SetHoveredColor(Color aColor) {
    this->hoveredColor = aColor;
}

void MyTextBox::SetText(const std::string& str) {
    this->text = str;
    this->cursorPosition = this->text.length();
}
