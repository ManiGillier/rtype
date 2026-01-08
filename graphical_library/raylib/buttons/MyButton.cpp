/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/

#include "MyButton.hpp"

MyButton::MyButton(int x, int y, int width, int height, int transparency)
    : m_x(x), m_y(y), m_width(width), m_height(height), m_transparency(transparency) {}

void MyButton::Draw() const {}

void MyButton::Update() {}

bool MyButton::IsClicked() const {
    return this->clicked;
}

bool MyButton::IsHovered() const {
    return this->hovered;
}

void MyButton::SetPosition(int x, int y) {
    this->posX = x;
    this->posY = y;
}

void MyButton::SetSize(int width, int height) {
    this->sizeX = width;
    this->sizeY = height;
}

void MyButton::SetTransparency(int transparency) {
    this->transparency = transparency;
}

void MyButton::SetColor(Color color) {
    this->color = color;
}

void MyButton::SetText(std::string str) {
    this->text = str;
}

void MyButton::OnClick() {
    this->clicked = true;
}
