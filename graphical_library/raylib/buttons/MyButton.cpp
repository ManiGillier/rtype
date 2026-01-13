/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/

#include "MyButton.hpp"

MyButton::MyButton(int x, int y, int width, int height,
    Color buttonColor, Color hoveredButtonColor, int transparency)
    : posX(x), posY(y), sizeX(width), sizeY(height),
    color(buttonColor), hoveredColor(hoveredButtonColor),
    transparency(transparency) {}

    void MyButton::draw() const {
        Rectangle buttonRect = {
            static_cast<float>(posX),
            static_cast<float>(posY),
            static_cast<float>(sizeX),
            static_cast<float>(sizeY)
        };
        Color currentColor = this->hovered ? this->hoveredColor : this->color;
        DrawRectangleRec(buttonRect, currentColor);
        DrawRectangleLinesEx(buttonRect, 2, BLACK);
        DrawText(
            this->text.c_str(),
            this->posX + 10,
            this->posY + (this->sizeY / 2) - 10,
            20,
            BLACK
        );
    }

void MyButton::update() {
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();

    if (((this->posX < mouseX) && (this->posX + this->sizeX > mouseX)) && ((this->posY < mouseY) && (this->posY + this->sizeY > mouseY)) )
        this->hovered = true;
    else
        this->hovered = false;
    if (isHovered() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        this->clicked = true;
    else
        this->clicked = false;
    return;
}

bool MyButton::isClicked() {
    return this->clicked;
}

bool MyButton::isHovered() {
    return this->hovered;
}

void MyButton::setPosition(int x, int y) {
    this->posX = x;
    this->posY = y;
}

void MyButton::setSize(int width, int height) {
    this->sizeX = width;
    this->sizeY = height;
}

void MyButton::setTransparency(int transparency) {
    this->transparency = transparency;
}

void MyButton::setColor(Color color) {
    this->color = color;
}

void MyButton::setHoveredColor(Color aColor) {
    this->hoveredColor = aColor;
}

void MyButton::setText(std::string str) {
    this->text = str;
}

void MyButton::switchClick() {
    this->clicked = true;
}
