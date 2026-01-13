#include "Check.hpp"
#include <iostream>
#include <raylib.h>

MyCheckBox::MyCheckBox(int x, int y, int size_, bool checked_,
    int transparency_)
    : hovered(false),
      checked(checked_),
      posX(x),
      posY(y),
      size(size_),
      transparency(transparency_),
      color({255, 255, 255, static_cast<unsigned char>(transparency_)}),
      text("") {}

void MyCheckBox::draw() const {
    Rectangle box = {
        static_cast<float>(posX),
        static_cast<float>(posY),
        static_cast<float>(size),
        static_cast<float>(size)
    };
    DrawRectangleRec(box, LIGHTGRAY);
    DrawRectangleLinesEx(box, 2, BLACK);
    if (this->checked) {
        DrawText("X", this->posX + 5, this->posY + 5, this->size - 10, BLACK);
    }
    if (!this->text.empty()) {
        DrawText(
            this->text.c_str(),
            this->posX + this->size + 10,
            this->posY + (this->size / 2) - 10,
            20,
            this->hovered ? this->hoveredColor : this->color
        );
    }
}

void MyCheckBox::update() {
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();

    if (((this->posX < mouseX) && (this->posX + this->size > mouseX)) && ((this->posY < mouseY) && (this->posY + this->size > mouseY)))
        this->hovered = true;
    else
        this->hovered = false;
    if (isHovered() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        this->checked = !this->checked;
    return;
}

bool MyCheckBox::isClicked() {
    return this->checked;
}

bool MyCheckBox::isHovered() {
    return this->hovered;
}

bool MyCheckBox::isChecked() const {
    return this->checked;
}

void MyCheckBox::setChecked(bool checked_) {
    this->checked = checked_;
}

void MyCheckBox::toggle() {
    this->checked = !this->checked;
}

void MyCheckBox::setPosition(int x, int y) {
    this->posX = x;
    this->posY = y;
}

void MyCheckBox::setSize(int size_) {
    this->size = size_;
}

void MyCheckBox::setTransparency(int transparency_) {
    this->transparency = transparency_;
}

void MyCheckBox::setColor(Color color_) {
    this->color = color_;
}

void MyCheckBox::setText(const std::string& str) {
    this->text = str;
}

void MyCheckBox::onClick() {
    this->toggle();
}

void MyCheckBox::setHoveredColor(Color aColor) {
    this->hoveredColor = aColor;
}
