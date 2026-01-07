/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/

#include "Button.hpp"

Button::Button(int x, int y, int width, int height, int transparency)
    : m_x(x), m_y(y), m_width(width), m_height(height), m_transparency(transparency) {}

void Button::Draw() const {}

void Button::Update() {}

bool Button::IsClicked() const {
    return this->clicked;
}

bool Button::IsHovered() const {
    return this->hovered;
}

void Button::SetPosition(int x, int y) {
    this->posX = x;
    this->posY = y;
}

void Button::SetSize(int width, int height) {
    this->sizeX = width;
    this->sizeY = height;
}

void Button::SetTransparency(int transparency) {
    this->transparency = transparency;
}

void Button::SetColor(Color color) {
    this->color = color;
}

void Button::SetText(std::string str) {
    this->text = str;
}

void Button::OnClick() {
    this->clicked = true;
}
