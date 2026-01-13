/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/

#include "MyInputBox.hpp"
#include <raylib.h>

MyInputBox::MyInputBox(int x, int y, int width, int height,
    Color boxColor, Color hoveredBoxColor, int transparency)
    : hovered(false), posX(x), posY(y), sizeX(width), sizeY(height),
    color(boxColor), hoveredColor(hoveredBoxColor),
    transparency(transparency), text(""), cursorPosition(0)
    {
        this->color = (Color){255, 255, 255, 150};
        this->activeColor = (Color){255, 255, 255, 255};
    }

void MyInputBox::draw() const {
    Rectangle boxRect = {
        static_cast<float>(posX),
        static_cast<float>(posY),
        static_cast<float>(sizeX),
        static_cast<float>(sizeY)
    };

    Color currentColor = this->active ? this->hoveredColor : this->color;
    DrawRectangleRec(boxRect, currentColor);

    if (this->active)
            DrawRectangleLinesEx(boxRect, 3, BLACK);
    else if (this->hovered)
        DrawRectangleLinesEx(boxRect, 2, GRAY);
    else
        DrawRectangleLinesEx(boxRect, 2, WHITE);

    DrawText(
        this->text.c_str(),
        this->posX + 10,
        this->posY + (this->sizeY / 2) - 10,
        20,
        BLACK
    );
}

void MyInputBox::update()
{
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();

    if (((this->posX < mouseX) && (this->posX + this->sizeX > mouseX)) && ((this->posY < mouseY) && (this->posY + this->sizeY > mouseY)))
        this->hovered = true;
    else
        this->hovered = false;

    if (isHovered() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        this->active = true;
    else if (!isHovered() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        this->active = false;

    if (this->active) {
            int key = GetCharPressed();
            while (key > 0) {
                if (key >= 32 && key <= 125) {
                    this->text += (char)key;
                }
                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE) && !this->text.empty()) {
                this->text.pop_back();
            }
        }
}

bool MyInputBox::isHovered() {

    return this->hovered;
}

void MyInputBox::setPosition(int x, int y) {
    this->posX = x;
    this->posY = y;
}

void MyInputBox::setSize(int width, int height) {
    this->sizeX = width;
    this->sizeY = height;
}

void MyInputBox::setTransparency(int transparency) {
    this->transparency = transparency;
}

void MyInputBox::setColor(Color color) {
    this->color = color;
}

void MyInputBox::setHoveredColor(Color aColor) {
    this->hoveredColor = aColor;
}

void MyInputBox::setText(const std::string& str) {
    this->text = str;
    this->cursorPosition = (int)this->text.length();
}

std::string MyInputBox::getText(void) {
    return this->text;
}
