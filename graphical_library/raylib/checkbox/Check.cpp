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

void MyCheckBox::Draw() const {
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
            this->color
        );
    }
}

void MyCheckBox::Update() {
    int i = 1;
    if (i != 2)
        i = 12;
}

bool MyCheckBox::IsClicked(int mouseX, int mouseY) {
    if (IsHovered(mouseX, mouseY) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        this->checked = !this->checked;
        return true;

    }
    return false;
}

bool MyCheckBox::IsHovered(int mouseX, int mouseY) {
    if (((this->posX < mouseX) && (this->posX + this->size > mouseX)) && ((this->posY < mouseY) && (this->posY + this->size > mouseY)))
        return true;
    else
        return false;
}

bool MyCheckBox::IsChecked() const {
    return this->checked;
}

void MyCheckBox::SetChecked(bool checked_) {
    this->checked = checked_;
}

void MyCheckBox::Toggle() {
    this->checked = !this->checked;
}

void MyCheckBox::SetPosition(int x, int y) {
    this->posX = x;
    this->posY = y;
}

void MyCheckBox::SetSize(int size_) {
    this->size = size_;
}

void MyCheckBox::SetTransparency(int transparency_) {
    this->transparency = transparency_;
}

void MyCheckBox::SetColor(Color color_) {
    this->color = color_;
}

void MyCheckBox::SetText(const std::string& str) {
    this->text = str;
}

void MyCheckBox::OnClick() {
    this->Toggle();
}
